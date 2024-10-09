#ifndef SCENE_H
#define SCENE_H

#include "mesh.hpp"
#include <vector>
#include "shader.hpp"
#include <string>
#include "IGameObject.hpp"
using std::vector, std::pair, std::string;

class Scene
{
    vector<IGameObject*> gameObjects;
    vector<IDrawableObject*> drawableObjects;
    vector<Shader*> shaders;

public:
    Scene() = default;
    ~Scene() = default;

    Scene(vector<IGameObject*> gObj, const string& shaderPath);
    vector<IGameObject*>* getObjects();
    vector<IDrawableObject*> getDrawableObjects();
    vector<Shader*>* getShaders();
    
};

#endif // SCENE_H