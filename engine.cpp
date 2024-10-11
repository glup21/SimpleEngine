// Provides render pipeline

#include "engine.hpp"
#include <iostream>

Engine::Engine() : drawObjectBuffer(){
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
    previousTime = std::chrono::high_resolution_clock::now();

    vertexPath = "../shaders/vertex.glsl";
    fragmentPath = "../shaders/fragment.glsl";

    shader = new Shader(vertexPath, fragmentPath);
}

void Engine::init(Scene scene)
{
    //Load and init shaders
    std::cout << "Initializing engine with scene." << std::endl;
    std::cout << "Engine object address: " << this << std::endl;

    drawObjectBuffer = scene.getDrawableObjects();
    gameObjects = *scene.getObjects();

    std::cout << "drawObjectBuffer address: " << &drawObjectBuffer << std::endl;
    std::cout << "drawObjectBuffer size: " << drawObjectBuffer.size() << std::endl;



}
void Engine::run()
{

    /*
        Clear screen
        Update game objects
        Draw each model
        Update other events
    
    */
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
        shader->use();
        dObj->draw(shader);
    }
}
float Engine::calculateDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}

// void Engine::setViewMatrix(const glm::mat4& view)
// {
//     shader->use();
//     shader->setMat4("view", view);
// }

// void Engine::setProjectionMatrix(const glm::mat4& projection)
// {
//     shader->use();
//     shader->setMat4("projection", projection);
// }