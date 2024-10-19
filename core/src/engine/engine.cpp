// Provides render pipeline

#include "engine.hpp"
#include <iostream>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"

bool isWindowFocused = true;
vector<bool> keys(100, false);

void window_focus_callback(GLFWwindow* window, int focused) {
    isWindowFocused = (focused == GLFW_TRUE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;  
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false; 
    }
}

Engine::Engine(GLFWwindow* window, CameraSettings cameraSettings) : drawObjectBuffer(){
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
    previousTime = std::chrono::high_resolution_clock::now();

    this->window = window;
    camera = new Camera(window, cameraSettings);

    vertexPath = "../core/src/engine/shaders/vertex.glsl";
    fragmentPath = "../core/src/engine/shaders/fragment.glsl";

    defaultShaderProgram = new ShaderProgram();
    Shader* vertexShader = ShaderFactory::createShader(GL_VERTEX_SHADER, vertexPath, camera);
    Shader* fragmentShader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, fragmentPath, camera);

    vertexShader->subscribe();

    defaultShaderProgram->attachShader(vertexShader);
    defaultShaderProgram->attachShader(fragmentShader);

    vertexShader->attachShaderProgram(defaultShaderProgram);

}

void Engine::init(string scenePath)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);

    lastMousePosition = inputManager->getMousePos();
    defaultShaderProgram->link(); //We will link individual shader programs in models if we want

    this->window = window;
}
void Engine::run()
{
    float deltaTime = calculateDeltaTime();
    glfwGetWindowSize(window, &width, &height);
    //mouse movement
    if(isWindowFocused)
    {
        glfwGetCursorPos(window, &xpos, &ypos);

        vec2 mouseDelta(width / 2.0 - xpos, height / 2.0 - ypos);

        if (glm::length(mouseDelta) > 0.01f)
        {
            mouseDelta = glm::normalize(mouseDelta);
            camera->changeTarget(-mouseDelta.x, mouseDelta.y, deltaTime);
        }
    }
    glfwSetCursorPos(window, width / 2.0, height / 2.0);

    //camera movement
    camera->move(keys, deltaTime);
    camera->notifySubscribers();

    // defaultShaderProgram->setMat4("projectionMatrix", camera->getProjectionMatrix());
    // defaultShaderProgram->setMat4("viewMatrix", camera->getViewMatrix());
    // defaultShaderProgram->setVec3("cameraPosition", camera->getPosition());

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
