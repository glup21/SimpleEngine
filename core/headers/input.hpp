#ifndef INPUT_H
#define INPUT_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "engine.hpp"
#include "camera.hpp"
#include "application.hpp"
#include <vector>

using glm::vec2;
using std::vector;

class Engine;
class Application;

class Input 
{
public:
    Input(GLFWwindow* window, Application* application, Engine* engine);

    void setEngine(Engine* newEngine);
    Engine* getEngine() { return engine; }

    void onKeyCallback(int key, int action);
    void onWindowFocus(int focused);

    void updateInput(const double& deltaTime);

private:
    Engine* engine;
    Application* application;
    GLFWwindow* window;
    bool isWindowFocused = true;
    vector<bool> keys;
    Camera* camera;
};

#endif
