// Provides render pipeline

#include "engine.hpp"
#include <iostream>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"


void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

Engine::Engine() : drawObjectBuffer(){
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
    previousTime = std::chrono::high_resolution_clock::now();

    vertexPath = "../shaders/vertex.glsl";
    fragmentPath = "../shaders/fragment.glsl";

    defaultShaderProgram = new ShaderProgram();
    Shader* vertexShader = ShaderFactory::createShader(GL_VERTEX_SHADER, vertexPath);
    Shader* fragmentShader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, fragmentPath);

    defaultShaderProgram->attachShader(vertexShader);
    defaultShaderProgram->attachShader(fragmentShader);

    camera = new Camera();

}

void Engine::init(string scenePath, GLFWwindow* window)
{
    glfwGetWindowSize(window, &width, &height);
    SceneReader sceneReader(scenePath);
    Scene scene = sceneReader.readScene(defaultShaderProgram);

    //Load and init shaders
    std::cout << "Initializing engine with scene." << std::endl;
    std::cout << "Engine object address: " << this << std::endl;

    drawObjectBuffer = scene.getDrawableObjects();
    gameObjects = *scene.getObjects();

    std::cout << "drawObjectBuffer address: " << &drawObjectBuffer << std::endl;
    std::cout << "drawObjectBuffer size: " << drawObjectBuffer.size() << std::endl;

    inputManager = new Input(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    lastMousePosition = inputManager->getMousePos();
    defaultShaderProgram->link(); //We will link individual shader programs in models if we want

    this->window = window;
}
void Engine::run()
{

    /*
        Clear screen
        Update game objects
        Draw each model
        Update other events
    
    */
    glfwGetWindowSize(window, &width, &height);

    // Get the current window size
    glfwGetWindowSize(window, &width, &height);

    // Center the cursor at the beginning of each frame
    glfwSetCursorPos(window, width / 2.0, height / 2.0);

    // Get the current mouse position (should be at the center now)
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Calculate the mouse delta using the center of the window
    glm::vec2 currentMousePosition(xpos, ypos);
    glm::vec2 mouseDelta = glm::vec2(width / 2.0, height / 2.0) - currentMousePosition;

    // Update the camera target based on mouse delta
    float sensitivity = 0.1f;
    camera->changeTarget(mouseDelta.x * sensitivity, -mouseDelta.y * sensitivity);


    defaultShaderProgram->setMat4("projectionMatrix", camera->getProjectionMatrix());
    defaultShaderProgram->setMat4("viewMatrix", camera->getViewMatrix());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updateGameObjects(calculateDeltaTime());
    drawObjects();

}
void Engine::shutdown()
{

}

void Engine::updateGameObjects(float delta)
{

    for(IGameObject* gObj : gameObjects)
        gObj->update(delta);

}
void Engine::drawObjects()
{
    for( IDrawableObject* dObj : drawObjectBuffer)
    {
        dObj->draw();
    }
}
float Engine::calculateDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}
