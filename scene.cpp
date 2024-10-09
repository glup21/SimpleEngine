#include "scene.hpp"
#include <iostream>

using std::cout, std::endl;

Scene::Scene(std::vector<IGameObject*> gObj, const std::string& shaderPath) : gameObjects(gObj)
{
    // REWORK FOR JSON CONFIG COMPATIBILITY LATER=

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

std::vector<IDrawableObject*> Scene::getDrawableObjects()
{
    return drawableObjects;
}
vector<Shader*>* Scene::getShaders()
{
    return &shaders;
}