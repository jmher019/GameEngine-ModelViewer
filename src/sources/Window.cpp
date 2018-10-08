#include <Window.hpp>

Window::Window(void) {}

Window::Window(const Window& window):
    width(window.width),
    height(window.height),
    fov(window.fov),
    nearZ(window.nearZ),
    farZ(window.farZ),
    projection(window.projection),
    camera(window.camera),
    title(window.title),
    window(nullptr) {
}

Window::Window(Window&& window):
    width(std::move(window.width)),
    height(std::move(window.height)),
    fov(std::move(window.fov)),
    nearZ(std::move(window.nearZ)),
    farZ(std::move(window.farZ)),
    projection(std::move(window.projection)),
    camera(std::move(window.camera)),
    title(std::move(window.title)),
    window(window.window),
    manager(std::move(window.manager)) {

    window.window = nullptr;
}

Window::~Window(void) {
    deallocate();
}

Window& Window::operator=(const Window& window) noexcept {
    setWidth(window.width);
    setHeight(window.height);
    setFOV(window.fov);
    setNearZ(window.nearZ);
    setFarZ(window.farZ);
    setTitle(window.title);
    camera = window.camera;

    return *this;
}

Window& Window::operator=(Window&& window) noexcept {
    width = std::move(window.width);
    height = std::move(window.height);
    fov = std::move(window.fov);
    nearZ = std::move(window.nearZ);
    farZ = std::move(window.farZ);
    projection = std::move(window.projection);
    camera = std::move(window.camera);
    title = std::move(window.title);
    manager = std::move(window.manager);

    deallocate();
    this->window = window.window;
    window.window = nullptr;

    return *this;
}

void Window::deallocate(void) noexcept {
    if (window == nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

void Window::updateProjectionMatrix(void) noexcept {
    projection = perspectiveFov(fov, (GLfloat)width, (GLfloat)height, nearZ, farZ);
    if (window != nullptr) {
        glViewport(0, 0, width, height);
    }
}

void Window::sizeCallback(GLFWwindow* window, GLint width, GLint height) {
    Window* parent = (Window*)glfwGetWindowUserPointer(window);
    parent->setWidth(width);
    parent->setHeight(height);

    WINDOW_RESIZE payload = {
        window,
        width,
        height
    };
    parent->manager.emit(payload);
}

void Window::keyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods) {
    Window* parent = (Window*)glfwGetWindowUserPointer(window);
    
    WINDOW_KEYEVENT payload = {
        window,
        key,
        action
    };

    parent->manager.emit(payload);
}

void Window::mouseCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
    Window* parent = (Window*)glfwGetWindowUserPointer(window);

    WINDOW_MOUSE_BUTTONEVENT payload = {
        window,
        button,
        action
    };
    parent->manager.emit(payload);
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    Window* parent = (Window*)glfwGetWindowUserPointer(window);

    WINDOW_CURSOR_POSITION payload = {
        window,
        xpos,
        ypos
    };

    parent->manager.emit(payload);
}

Window& Window::setTitle(const string& title) noexcept {
    this->title = title;

    if (window != nullptr) {
        glfwSetWindowTitle(window, title.c_str());
    }

    return *this;
}

Window& Window::setWidth(const GLint& width) noexcept {
    this->width = width;
    updateProjectionMatrix();
    return *this;
}

Window& Window::setHeight(const GLint& height) noexcept {
    this->height = height;
    updateProjectionMatrix();
    return *this;
}

Window& Window::setFOV(const GLfloat& fov) noexcept {
    this->fov = fov;
    updateProjectionMatrix();
    return *this;
}

Window& Window::setNearZ(const GLfloat& nearZ) noexcept {
    this->nearZ = nearZ;
    updateProjectionMatrix();
    return *this;
}

Window& Window::setFarZ(const GLfloat& farZ) noexcept {
    this->farZ = farZ;
    updateProjectionMatrix();
    return *this;
}

Window& Window::setEyePosition(const vec3& eyePosition) noexcept {
    camera.setEyePosition(eyePosition);
    return *this;
}

Window& Window::setLookAtPosition(const vec3& lookAtPosition) noexcept {
    camera.setLookAtPosition(lookAtPosition);
    return *this;
}

Window& Window::setUpVector(const vec3& upVector) noexcept {
    camera.setUpVector(upVector);
    return *this;
}

void Window::initialize(void) {
    deallocate();

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        throw exception("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Window::sizeCallback);
    glfwSetKeyCallback(window, Window::keyCallback);
    glfwSetMouseButtonCallback(window, Window::mouseCallback);
    glfwSetCursorPosCallback(window, Window::cursorPositionCallback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw exception("Failed to initialize OpenGL context");
    }

    // glad populates global constants after loading to indicate,
    // if a certain extension/version is available.
    cout << "OpenGL " << glGetString(GL_VERSION) << endl;
    cout << "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "Renderer " << glGetString(GL_RENDERER) << endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLFWwindow* Window::getWindow(void) noexcept {
    return window;
}

const Camera& Window::getCamera(void) const noexcept {
    return camera;
}

void Window::setCamera(Camera& camera) noexcept {
    this->camera = camera;
}

mat4 Window::getProjectionViewMatrix(void) const noexcept {
    return projection * camera.getCameraMatrix();
}

void Window::subscribeToResize(function<void(const WINDOW_RESIZE&)> callable) noexcept {
    manager.subscribe<WINDOW_RESIZE>(callable);
}

void Window::subscribeToKeyEvents(function<void(const WINDOW_KEYEVENT&)> callable) noexcept {
    manager.subscribe<WINDOW_KEYEVENT>(callable);
}

void Window::subscribeToMouseButtonEvents(function<void(const WINDOW_MOUSE_BUTTONEVENT&)> callable) noexcept {
    manager.subscribe<WINDOW_MOUSE_BUTTONEVENT>(callable);
}

void Window::subscribeToCursorPositionEvents(function<void(const WINDOW_CURSOR_POSITION&)> callable) noexcept {
    manager.subscribe<WINDOW_CURSOR_POSITION>(callable);
}