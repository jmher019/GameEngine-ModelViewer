#ifndef MODEL_VIEWER_HPP
#define MODEL_VIEWER_HPP

#include <MeshFactory.hpp>
#include <ShaderFactory.hpp>
#include <Window.hpp>
#include <SceneGraph.hpp>
#include <LogRendererSystem.hpp>

#include <chrono>
#include <limits>

class ModelViewer {
private:
    shared_ptr<Mesh> mesh = nullptr;
    shared_ptr<SceneObject> world = nullptr;
    Window window = Window();

    double mouseX = numeric_limits<double>::max();
    double mouseY = numeric_limits<double>::max();

    bool mouseLeftPressed = false;
    bool mouseMiddlePressed = false;
    bool mouseRightPressed = false;
    bool keys[GLFW_KEY_LAST + 1];

    void setupInputSubscriptions(void) noexcept;

    void onKeyEvent(const WINDOW_KEYEVENT& e) noexcept;

    void handleKeyPress(GLFWwindow* window, const int& key) noexcept;

    void handleKeyRelease(GLFWwindow* window, const int& key) noexcept;

    void onMouseButtonEvent(const WINDOW_MOUSE_BUTTONEVENT& e) noexcept;

    void handleMouseButtonPress(GLFWwindow* window, const int& key) noexcept;

    void handleMouseButtonRelease(GLFWwindow* window, const int& key) noexcept;

    void onCursorPositionChange(const WINDOW_CURSOR_POSITION& e) noexcept;

    void translateWorld(const float& tX, const float& tY, const float& tZ) noexcept;

    void rotateWorld(const float& degreesX, const float& degreesY, const float& degreesZ) noexcept;

public:
    ModelViewer(void);

    void setModelToLoad(const MeshConstants& key) noexcept;

    void setShaderForModel(const ShaderConstants& key) noexcept;

    void run(void) noexcept;
};

#endif // !MODEL_VIEWER_HPP
