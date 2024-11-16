#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.hpp"
#include "shaderProgram.hpp"
#include "camera.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <glm/vec2.hpp>
#include "input.hpp"
#include "cameraSettings.hpp"
#include "configReader.hpp"

using glm::vec2;

class Input;

class Engine
{
private:
    vector<IDrawableObject*> drawObjectBuffer;
    vector<shared_ptr<IGameObject>> gameObjects;
    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
    ShaderProgram* defaultShaderProgram;
    Camera* camera;
    vec2 lastMousePosition;
    GLFWwindow* window;
    ConfigReader* configReader;
    Input* input;
    int width;
    int height;

    double xpos, ypos;

    string vertexPath;
    string fragmentPath;

    void updateGameObjects(float delta);
    void drawObjects();
    


public:
    Engine(GLFWwindow* window, ConfigReader* configReader);
    ~Engine() = default;
    void init(string scenePath);
    void run();
    void shutdown();

    Camera* getCamera();
    double getDeltaTime();
    void addInput(Input* input);
};

#endif