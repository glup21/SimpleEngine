// Provides render pipeline

#include "engine.h"
#include <iostream>

Engine::Engine() : drawObjectBuffer(nullptr), shaderProgram(new ShaderProgram()) {
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
}

void Engine::init(Scene scene)
{
    //Load and init objects
    //Load and init shaders
    //Link shaderProgram
    std::cout << "Initializing engine with scene." << std::endl;

    // Check the address of the Engine object
    std::cout << "Engine object address: " << this << std::endl;

    drawObjectBuffer = scene.getDrawableObjects();

    if (!drawObjectBuffer) {
        std::cerr << "Error: drawObjectBuffer is null." << std::endl;
        return;
    }

    std::cout << "drawObjectBuffer address: " << drawObjectBuffer << std::endl;
    std::cout << "drawObjectBuffer size: " << drawObjectBuffer->size() << std::endl;

    for (size_t i = 0; i < drawObjectBuffer->size(); ++i) {
        IDrawableObject* obj = (*drawObjectBuffer)[i];
        if (obj) {
            std::cout << "Setting up drawable object at index " << i << std::endl;
            obj->setup();
        } else {
            std::cerr << "Error: Null drawable object encountered at index " << i << std::endl;
        }
    }

    vector<Shader*>* shaders = scene.getShaders();

    for(Shader* shader : *shaders)
    {
        shaderProgram->attachShader(*shader);
    }
    shaderProgram->linkProgram();
    
}
void Engine::run()
{
    // while (!glfwWindowShouldClose(window)){
    //     // clear color and depth buffer
    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //     glUseProgram(shaderProgram);
    //     glBindVertexArray(VAO);

    //     // draw triangles
    //     glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count

    //     glBindVertexArray(square_VAO);
    //     glDrawArrays(GL_TRIANGLES, 0, 6);
    //     // update other events like input handling
    //     glfwPollEvents();
    //     // put the stuff we’ve been drawing onto the display
    //     glfwSwapBuffers(window);
    // }

    /*
        Clear screen
        Use shaderProgram
        Draw each model
        Update other events
    
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->use();
    for( IDrawableObject* dObj : *drawObjectBuffer)
    {
        dObj->draw();
    }
    glfwPollEvents();


}
void Engine::shutdown()
{

}