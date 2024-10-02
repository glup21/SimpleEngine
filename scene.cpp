#include "scene.h"
#include <iostream>

using std::cout, std::endl;

Scene::Scene(std::vector<IGameObject*> gObj, const std::string& shaderPath) : gameObjects(gObj)
{
    // REWORK FOR JSON CONFIG COMPATIBILITY LATER
    std::vector<std::pair<GLenum, std::string>> shaderTypes = 
        { {GL_VERTEX_SHADER, "vertex.glsl"}, {GL_FRAGMENT_SHADER, "fragment.glsl"}};
    
    for (const std::pair<GLenum, std::string>& shaderPair : shaderTypes)
    {   
        std::string path = shaderPath + shaderPair.second;
        std::cout << "Loading shader from path: " << path << std::endl;
        Shader* shader = new Shader(path, shaderPair.first);
        if (shader)
        {
            shaders.push_back(shader);
            std::cout << "Shader loaded and added to shaders vector." << std::endl;
        }
        else
        {
            std::cerr << "Failed to load shader from path: " << path << std::endl;
        }
    }

    std::cout << "Number of game objects: " << gameObjects.size() << std::endl;

    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        IGameObject* obj = gameObjects[i];
        if (obj)
        {
            std::cout << "Processing game object at index " << i << std::endl;
            IDrawableObject* drawable = dynamic_cast<IDrawableObject*>(obj);
            if (drawable)
            {
                drawableObjects.push_back(drawable);
                std::cout << "Drawable object added to drawableObjects vector." << std::endl;
            }
            else
            {
                std::cerr << "Failed to cast IGameObject to IDrawableObject at index " << i << std::endl;
            }
        }
        else
        {
            std::cerr << "Null IGameObject pointer encountered at index " << i << std::endl;
        }
    }

    std::cout << "Number of drawable objects: " << drawableObjects.size() << std::endl;
}

std::vector<IGameObject*>* Scene::getObjects()
{
    return &gameObjects;
}

std::vector<IDrawableObject*>* Scene::getDrawableObjects()
{
    return &drawableObjects;
}
vector<Shader*>* Scene::getShaders()
{
    return &shaders;
}