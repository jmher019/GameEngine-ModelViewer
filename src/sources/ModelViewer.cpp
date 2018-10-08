#include <ModelViewer.hpp>

ModelViewer::ModelViewer(void) {
    window.setWidth(512)
        .setHeight(512)
        .setTitle(string("Model Viewer 1.0.0"));

    window.initialize();

    setupInputSubscriptions();

    world = make_shared<SceneObject>(string("World"));

    for (int i = 0; i < GLFW_KEY_LAST + 1; i++) {
        keys[i] = false;
    }
}

void ModelViewer::setupInputSubscriptions(void) noexcept {
    window.subscribeToKeyEvents([this](const WINDOW_KEYEVENT& e) {
        this->onKeyEvent(e);
    });

    window.subscribeToMouseButtonEvents([this](const WINDOW_MOUSE_BUTTONEVENT& e) {
        this->onMouseButtonEvent(e);
    });

    window.subscribeToCursorPositionEvents([this](const WINDOW_CURSOR_POSITION& e) {
        this->onCursorPositionChange(e);
    });
}

void ModelViewer::onKeyEvent(const WINDOW_KEYEVENT& e) noexcept {
    switch (e.action) {
        case GLFW_PRESS: {
            this->handleKeyPress(e.window, e.key);
            break;
        }
        case GLFW_RELEASE: {
            this->handleKeyRelease(e.window, e.key);
            break;
        }
    }
}

void ModelViewer::handleKeyPress(GLFWwindow* window, const int& key) noexcept {
    keys[key] = true;
    
    switch (key) {
        case GLFW_KEY_ESCAPE: {
            glfwSetWindowShouldClose(window, true);
            break;
        }
        case GLFW_KEY_Q: {
            world->update(world->getTransform().getInverse());
            break;
        }
    }
}

void ModelViewer::handleKeyRelease(GLFWwindow* window, const int& key) noexcept {
    keys[key] = false;
}

void ModelViewer::onMouseButtonEvent(const WINDOW_MOUSE_BUTTONEVENT& e) noexcept {
    switch (e.action) {
        case GLFW_PRESS: {
            this->handleMouseButtonPress(e.window, e.button);
            break;
        }
        case GLFW_RELEASE: {
            this->handleMouseButtonRelease(e.window, e.button);
            break;
        }
    }
}

void ModelViewer::handleMouseButtonPress(GLFWwindow* window, const int& key) noexcept {
    switch (key) {
        case GLFW_MOUSE_BUTTON_MIDDLE: {
            mouseMiddlePressed = true;
            break;
        }
        case GLFW_MOUSE_BUTTON_LEFT: {
            mouseLeftPressed = true;
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            mouseRightPressed = true;
            break;
        }
    }
}

void ModelViewer::handleMouseButtonRelease(GLFWwindow* window, const int& key) noexcept {
    switch (key) {
        case GLFW_MOUSE_BUTTON_MIDDLE: {
            mouseMiddlePressed = false;
            break;
        }
        case GLFW_MOUSE_BUTTON_LEFT: {
            mouseLeftPressed = false;
            break;
        }
        case GLFW_MOUSE_BUTTON_RIGHT: {
            mouseRightPressed = false;
            break;
        }
    }
}

void ModelViewer::onCursorPositionChange(const WINDOW_CURSOR_POSITION& e) noexcept {
    if (mouseX != numeric_limits<double>::max() && mouseY != numeric_limits<double>::max()) {
        float delX = static_cast<float>(e.xpos - mouseX);
        float delY = static_cast<float>(e.ypos - mouseY);

        if (mouseMiddlePressed) {
            if (keys[GLFW_KEY_W]) {
                translateWorld(delX * .1f, -delY * .1f, 0.f);
            }
            else if (keys[GLFW_KEY_E]) {
                rotateWorld(-delY * .1f, delX * .1f, 0.f);
            }
            else if (keys[GLFW_KEY_R]) {
            }
        }
    }

    mouseX = e.xpos;
    mouseY = e.ypos;
}

void ModelViewer::translateWorld(const float& tX, const float& tY, const float& tZ) noexcept {
    world->update(Transform(fdualquat(fquat(1.f, 0.f, 0.f, 0.f), vec3(tX, tY, tZ))));
}

void ModelViewer::rotateWorld(const float& degreesX, const float& degreesY, const float& degreesZ) noexcept {
    world->rotate(degreesX, degreesY, degreesZ);
}

void ModelViewer::setModelToLoad(const MeshConstants& key) noexcept {
    mesh = MeshFactory::getMesh(key);
}

void ModelViewer::setShaderForModel(const ShaderConstants& key) noexcept {
    if (mesh != nullptr) {
        mesh->setShader(ShaderFactory::getShader(key));
    }
}

void ModelViewer::run(void) noexcept {
    world->appendChild(mesh);
    SceneGraph graph(world);

    mat4 orthoProj = ortho(0.f, static_cast<GLfloat>(512), static_cast<GLfloat>(512), 0.f);
    /*shared_ptr<UIElement> ui = make_shared<UIElement>();
    ui->setShader(ShaderFactory::getShader(ShaderConstants::UI_SHADER));
    ui->setTextShader(ShaderFactory::getShader(ShaderConstants::TEXT_SHADER));
    ui->setFillColor(vec4(1.f, 1.f, 0.f, 1.f));
    ui->setTextColor(vec4(0.f, 1.f, 0.f, 1.f));
    ui->setFontSize(24.f);
    ui->translate(256.f, 256.f);
    ui->rotate(45.f);
    ui->setText("This is a test. This is a test. This is a test. This is a test.\nThis is a test.\nThis is a test.");
    ui->setTextAlign(TextAlign::CENTER);
    ui->setWidth(256);
    ui->setWordWrap(true);

    shared_ptr<UIElement> ui2 = make_shared<UIElement>();
    ui2->setShader(ShaderFactory::getShader(ShaderConstants::UI_SHADER));
    ui2->setTextShader(ShaderFactory::getShader(ShaderConstants::TEXT_SHADER));
    ui2->setFillColor(vec4(1.f, 0.f, 1.f, .5f));
    ui2->setFontSize(24.f);
    ui2->translate(256.f, 256.f);
    ui2->rotate(45.f);
    ui2->setZIndex(2.f);
    ui2->setText("my my");
    ui2->setTextColor(vec4(1.f, 1.f, 1.f, .5f));*/

    LogRendererSystem::setUIShader(ShaderFactory::getShader(ShaderConstants::UI_SHADER));
    LogRendererSystem::setTextShader(ShaderFactory::getShader(ShaderConstants::TEXT_SHADER));

    chrono::system_clock::time_point currentTime = chrono::system_clock::now();
    chrono::system_clock::time_point previousTime = currentTime;

    constexpr GLuint framesForPrint = 60;
    GLuint frames = 0;
    GLfloat timePassed = 0.f;

    while (!glfwWindowShouldClose(window.getWindow())) {
        currentTime = chrono::system_clock::now();
        chrono::duration<float> elapsedSeconds = currentTime - previousTime;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        graph.draw(window.getProjectionViewMatrix());
        /*ui->draw(orthoProj);
        ui2->draw(orthoProj);*/

        ++frames;
        timePassed += elapsedSeconds.count();

        if (framesForPrint == frames) {
            LogRendererSystem::overwriteTopLogMessage(to_string(1.f / (timePassed / static_cast<GLfloat>(framesForPrint))) + string(" FPS"), 4.f, LogMessageType::LOG_NORMAL);
            frames = 0;
            timePassed = 0.f;
        }
        LogRendererSystem::renderMessages(orthoProj);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();

        previousTime = currentTime;
    }
}