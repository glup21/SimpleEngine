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

    camera = std::make_unique<Camera>(window, configReader->getCameraSettings());
    auto vertexShader = ShaderFactory::createShader(GL_VERTEX_SHADER, configReader->getVertexShaderPath(), camera.get());
    auto fragmentShader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, configReader->getFragmentShaderPath(), camera.get());

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    defaultShaderProgram = std::make_unique<ShaderProgram>(vertexShader, fragmentShader);
    defaultShaderProgram->observe(camera.get());

}

void Engine::init(const std::string& scenePath)
{


    glfwGetWindowSize(window, &width, &height);

    SceneReader sceneReader(scenePath);
    Scene scene = sceneReader.readScene(defaultShaderProgram.get());
    drawableObjects = scene.getDrawableObjects();
    gameObjects = scene.getObjects();
    // Calling updateLight from Engine is dumb, and must be handled
    // by ShaderProgram. Fix later
    
    defaultShaderProgram->updateLight();

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
