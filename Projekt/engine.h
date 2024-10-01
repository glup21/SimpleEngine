#ifndef ENGINE_H
#define ENGINE_H

#include "scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

class Engine
{

    vector<IDrawableObject*>* drawObjectBuffer;

public:
    Engine() = default;
    ~Engine() = default;
    void init(Scene scene);
    void run();
    void shutdown();

};

#endif