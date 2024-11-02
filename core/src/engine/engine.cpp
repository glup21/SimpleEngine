#include "engine.hpp"
#include <iostream>
#include <thread>
#include <glm/glm.hpp>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"

bool isWindowFocused = true;
vector<bool> keys(100, false);

void window_focus_callback(GLFWwindow* window, int focused) 
{
    isWindowFocused = (focused == GLFW_TRUE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{

    if (action == GLFW_PRESS) {
        keys[key] = true;

        if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) 
        {
            int sceneID = key - GLFW_KEY_0; 
            Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));

            engine->loadScene(sceneID-1); 

        }
    } else if (action == GLFW_RELEASE) 
        keys[key] = false;
    
}

Engine::Engine(GLFWwindow* window, ConfigReader* configReader) 
    : window(window), configReader(configReader) 
{
    previousTime = std::chrono::high_resolution_clock::now();

    camera = new Camera(window, configReader->getCameraSettings());

    defaultShaderProgram = new ShaderProgram();
    defaultShaderProgram->observe(camera);

    Shader* vertexShader = ShaderFactory::createShader(GL_VERTEX_SHADER, configReader->getVertexShaderPath(), camera);
    Shader* fragmentShader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, configReader->getFragmentShaderPath(), camera);

    defaultShaderProgram->attachShader(vertexShader);
    defaultShaderProgram->attachShader(fragmentShader);
    defaultShaderProgram->link();

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);
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

    drawObjectBuffer = scene.getDrawableObjects();
    gameObjects = *scene.getObjects();
}

void Engine::run() 
{
    double targetFPS = 60.0; 
    double targetFrameTime = 1.0 / targetFPS; 

    while (!glfwWindowShouldClose(window)) 
    {
        auto frameStartTime = std::chrono::high_resolution_clock::now();  
        double deltaTime = calculateDeltaTime();


        glfwGetWindowSize(window, &width, &height);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        glm::vec2 mouseDelta(width / 2.0 - xpos, height / 2.0 - ypos);

        if (isWindowFocused && glm::length(mouseDelta) > 0.01f) 
        {
            mouseDelta = glm::normalize(mouseDelta);
            camera->changeTarget(-mouseDelta.x, mouseDelta.y, deltaTime);
        }
        glfwSetCursorPos(window, width / 2.0, height / 2.0);

        camera->move(keys, deltaTime);
        camera->notifyObservers();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateGameObjects(deltaTime);
        drawObjects();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // FPS control
        auto frameEndTime = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> frameDuration = frameEndTime - frameStartTime;

        if (frameDuration.count() < targetFrameTime) 
            std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameTime - frameDuration.count()));
        
    }
}


void Engine::loadScene(int sceneID) 
{
    string scenePath = configReader->getScenePath(sceneID);
    if (!scenePath.empty()) {
        std::cout << "Loading scene: " << scenePath << std::endl;
        init(scenePath); 
    } 
    else 
        std::cerr << "Error: Scene ID " << sceneID << " is out of range." << std::endl;
    
}


void Engine::shutdown() 
{
    delete camera;
    delete defaultShaderProgram;
}


void Engine::updateGameObjects(float delta) 
{
    for (auto& gObj : gameObjects)
        gObj->update(delta);
}


void Engine::drawObjects()
{
    for (auto dObj : drawObjectBuffer) 
        dObj->draw();
    
}


double Engine::calculateDeltaTime() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}
