#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "engine.h"
#include "scene.h"
#include "mesh.h"

class Application
{

    Engine* engine;
    GLFWwindow* window;

public:
    Application() = default;
    ~Application() = default;

    void initialize();
    void run();
    void shutdown();

};

#endif