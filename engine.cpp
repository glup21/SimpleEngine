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

void Engine::init(string scenePath)
{
    SceneReader sceneReader(scenePath);
    Scene scene = sceneReader.readScene(defaultShaderProgram);

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



    defaultShaderProgram->link(); //We will link individual shader programs in models if we want

    printMat4(camera->getViewMatrix());

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
