#ifndef SCENE_H
#define SCENE_H

#include "mesh.h"
#include <vector>

using std::vector;

class Scene
{

    vector<IDrawableObject*> drawObjects;

public:
    Scene() = default;
    ~Scene() = default;

    Scene(vector<IDrawableObject*> dObj);
    vector<IDrawableObject*>* getObjects();


};

#endif