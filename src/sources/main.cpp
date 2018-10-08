#include <ModelViewer.hpp>

#include <chrono>
#include <thread>

using namespace std;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit()) {
        printf("failed to initialize GLFW.\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    try {
        // First create the viewer in order to initalize an GLFW context
        ModelViewer viewer;

        FontSystem::startUp();
        TextRenderingSystem::startUp();
        LogRendererSystem::startUp();

        FontSystem::loadFace("C:\\Windows\\Fonts\\arial.ttf", FontKey::ARIAL);
        
        // Now load the mesh
        cout << "Loading mesh" << endl;
        MeshFactory::loadAndCacheMesh(string("..\\assets\\bunny.obj"), MeshConstants::BUNNY);
        cout << "Finished loading mesh" << endl;

        // Load the shader too
        ShaderFactory::loadAndCacheShader(string("..\\shaders\\normal-shader.vert"), string("..\\shaders\\normal-shader.frag"), ShaderConstants::NORMAL_SHADER);
        ShaderFactory::loadAndCacheShader(string("..\\shaders\\ui-shader.vert"), string("..\\shaders\\ui-shader.frag"), ShaderConstants::UI_SHADER);
        ShaderFactory::loadAndCacheShader(string("..\\shaders\\text-shader.vert"), string("..\\shaders\\text-shader.frag"), ShaderConstants::TEXT_SHADER);

        // Set the mesh and shader to use
        viewer.setModelToLoad(MeshConstants::BUNNY);
        viewer.setShaderForModel(ShaderConstants::NORMAL_SHADER);

        // Run viewer
        viewer.run();
        
        LogRendererSystem::shutDown();
        TextRenderingSystem::shutDown();
        FontSystem::shutDown();

        glfwTerminate();
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
    return EXIT_SUCCESS;
}