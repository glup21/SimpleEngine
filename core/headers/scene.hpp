#ifndef SCENE_H
#define SCENE_H

#include "mesh.hpp"
#include <vector>
#include "shader.hpp"
#include <string>
#include "IGameObject.hpp"
#include <memory>
using std::vector, std::pair, std::string, std::shared_ptr;

class Scene
{
    vector<shared_ptr<IGameObject>> gameObjects;
    vector<IDrawableObject*> drawableObjects;
    vector<Shader*> shaders; // I dont need this

public:
    Scene() = default;
    ~Scene() = default;

    Scene(vector<shared_ptr<IGameObject>> gObj);
    vector<shared_ptr<IGameObject>>* getObjects();
    vector<IDrawableObject*> getDrawableObjects();
    vector<Shader*>* getShaders();
    
};

#endif 