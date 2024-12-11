#include "engine.hpp"
#include <iostream>
#include <thread>
#include <glm/glm.hpp>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"
#include "MaterialFactory.hpp"

Engine::Engine(GLFWwindow* window, ConfigReader* configReader)
    : window(window), configReader(configReader)
{
    previousTime = std::chrono::high_resolution_clock::now();
    camera = std::make_shared<Camera>(window, configReader->getCameraSettings());

    MaterialFactory& mf = MaterialFactory::getInstance();
    mf.setCamera(camera.get());
    mf.setShaderPath("../core/src/engine/shaders/");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

}

void Engine::init(const std::string& scenePath)
{


    glfwGetWindowSize(window, &width, &height);

    SceneReader sceneReader(scenePath);
    Scene scene = sceneReader.readScene();
    drawableObjects = scene.getDrawableObjects();
    gameObjects = scene.getObjects();
    
    // Calling updateLight from Engine is dumb, and must be handled
    // by ShaderProgram. Fix later
    MaterialFactory& mf = MaterialFactory::getInstance();
    mf.updateAllLights();

    

    std::cout << "Init finished\n" << std::endl;
}

void Engine::run()
{

    while (!glfwWindowShouldClose(window))
    {
        double deltaTime = getDeltaTime();
        glfwPollEvents();

        input->updateInput(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateGameObjects(deltaTime);
        drawObjects();

        glfwSwapBuffers(window);
        
    }
}

void Engine::shutdown()
{
    input.reset();
    drawableObjects.clear();
    gameObjects.clear();
}

void Engine::updateGameObjects(float delta)
{
    for (auto& gObj : gameObjects)
        gObj->update(delta);
}

void Engine::drawObjects()
{
    for (auto& dObj : drawableObjects)
        dObj->draw();
}

double Engine::getDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}
