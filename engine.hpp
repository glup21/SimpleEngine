#ifndef ENGINE_H
#define ENGINE_H

#include "scene.hpp"
#include "shaderProgram.hpp"
#include "camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <glm/vec2.hpp>
#include "input.hpp"

using glm::vec2;

class Engine
{
private:
    vector<IDrawableObject*> drawObjectBuffer;
    vector<IGameObject*> gameObjects;
    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
    ShaderProgram* defaultShaderProgram;
    Camera* camera;
    Input* inputManager;
    vec2 lastMousePosition;
    GLFWwindow* window;
    int width;
    int height;

    string vertexPath;
    string fragmentPath;

    void updateGameObjects(float delta);
    void drawObjects();
    float calculateDeltaTime();


public:
    Engine();
    ~Engine() = default;
    void init(string scenePath, GLFWwindow* window);
    void run();
    void shutdown();

};

#endif