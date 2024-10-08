#ifndef ENGINE_H
#define ENGINE_H

#include "scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include "shaderProgram.h"
#include <chrono>

class Engine
{

    vector<IDrawableObject*> drawObjectBuffer;
    vector<IGameObject*> gameObjects;
    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
    //ShaderProgram* shaderProgram;

    void updateGameObjects(float delta);
    void drawObjects();
    float calculateDeltaTime();

public:
    Engine();
    ~Engine() = default;
    void init(Scene scene);
    void run();
    void shutdown();

};

#endif