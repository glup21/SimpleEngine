#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "engine.hpp"
#include "scene.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "configReader.hpp"
#include "input.hpp"

class Engine;
class Input;

class Application
{

    Engine* engine;
    GLFWwindow* window;
    ConfigReader* configReader;
    string scenePath;
    Input* input;

public:
    Application(ConfigReader* configReader);
    ~Application() = default;

    void initialize();
    void run();
    void shutdown();
    void critical_shutdown();
    void loadScene(int sceneID);

};

#endif