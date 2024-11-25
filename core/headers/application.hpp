#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "engine.hpp"
#include "configReader.hpp"
#include "input.hpp"

class Engine;
class Input;

class Application
{
    std::unique_ptr<Engine> engine;
    GLFWwindow* window;
    ConfigReader* configReader; 
    std::string scenePath;
    std::shared_ptr<Input> input;

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
