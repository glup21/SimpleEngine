// Provides render pipeline

#include "engine.h"
#include <iostream>

Engine::Engine() : drawObjectBuffer(), shaderProgram(new ShaderProgram()) {
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
}

void Engine::init(Scene scene)
{
    //Load and init shaders
    std::cout << "Initializing engine with scene." << std::endl;
    std::cout << "Engine object address: " << this << std::endl;

    drawObjectBuffer = scene.getDrawableObjects();

    std::cout << "drawObjectBuffer address: " << &drawObjectBuffer << std::endl;
    std::cout << "drawObjectBuffer size: " << drawObjectBuffer.size() << std::endl;

    vector<Shader*>* shaders = scene.getShaders();

    for(Shader* shader : *shaders)
    {
        shaderProgram->attachShader(*shader);
    }
    shaderProgram->linkProgram();
    
}
void Engine::run()
{

    /*
        Clear screen
        Use shaderProgram
        Draw each model
        Update other events
    
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->use();
    for( IDrawableObject* dObj : drawObjectBuffer)
    {
        dObj->draw();


    }



}
void Engine::shutdown()
{

}