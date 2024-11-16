#include "engine.hpp"
#include <iostream>
#include <thread>
#include <glm/glm.hpp>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"

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
        double deltaTime = getDeltaTime();
        input->updateInput(deltaTime);

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


double Engine::getDeltaTime() 
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}

Camera* Engine::getCamera()
{
    return camera;
}

void Engine::addInput(Input* input)
{
    this->input = input;
}