#ifndef SCENE_H
#define SCENE_H

#include "mesh.h"
#include <vector>
#include "shader.h"
#include <string>
#include "IGameObject.h"
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