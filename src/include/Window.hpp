#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <EventManager.hpp>
#include <Vertex.hpp>
#include <Camera.hpp>

#include <GLFW\glfw3.h>

struct WINDOW_RESIZE {
    GLFWwindow* window;
    int width;
    int height;
};

struct WINDOW_KEYEVENT {
    GLFWwindow* window;
    int key;
    int action;
};

struct WINDOW_MOUSE_BUTTONEVENT {
    GLFWwindow* window;
    int button;
    int action;
};

struct WINDOW_CURSOR_POSITION {
    GLFWwindow* window;
    double xpos;
    double ypos;
};

class Window {
private:
    GLint width = 512;
    GLint height = 512;
    GLfloat fov = 45.f;
    GLfloat nearZ = 0.1f;
    GLfloat farZ = 100.f;
    mat4 projection = perspectiveFov(fov, (GLfloat)width, (GLfloat)height, nearZ, farZ);
    Camera camera;
    string title = string("Model Viewer");
    EventManager manager;
    GLFWwindow* window = nullptr;

    void deallocate(void) noexcept;
    void updateProjectionMatrix(void) noexcept;

    static void sizeCallback(GLFWwindow* window, GLint width, GLint height);
    static void keyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
    static void mouseCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

public:
    Window(void);

    Window(const Window& window);

    Window(Window&& window);

    ~Window(void);

    Window& operator=(const Window& window) noexcept;

    Window& operator=(Window&& window) noexcept;

    Window& setTitle(const string& title) noexcept;

    Window& setWidth(const GLint& width) noexcept;

    Window& setHeight(const GLint& height) noexcept;

    Window& setFOV(const GLfloat& fov) noexcept;

    Window& setNearZ(const GLfloat& nearZ) noexcept;

    Window& setFarZ(const GLfloat& farZ) noexcept;

    Window& setEyePosition(const vec3& eyePosition) noexcept;

    Window& setLookAtPosition(const vec3& lookAtPosition) noexcept;

    Window& setUpVector(const vec3& upVector) noexcept;

    void initialize(void);

    GLFWwindow* getWindow(void) noexcept;

    const Camera& getCamera(void) const noexcept;

    void setCamera(Camera& camera) noexcept;

    mat4 getProjectionViewMatrix(void) const noexcept;

    void subscribeToResize(function<void(const WINDOW_RESIZE&)> callable) noexcept;

    void subscribeToKeyEvents(function<void(const WINDOW_KEYEVENT&)> callable) noexcept;

    void subscribeToMouseButtonEvents(function<void(const WINDOW_MOUSE_BUTTONEVENT&)> callable) noexcept;

    void subscribeToCursorPositionEvents(function<void(const WINDOW_CURSOR_POSITION&)> callable) noexcept;
};

#endif // !WINDOW_HPP