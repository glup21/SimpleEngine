#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include <string>
#include <chrono>
#include <glm/vec2.hpp>
#include "shaderProgram.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "configReader.hpp"
#include "IGameObject.hpp"
#include "IDrawableObject.hpp"

class Input;

class Engine
{
private:
    std::vector<std::shared_ptr<IDrawableObject>> drawableObjects;
    std::vector<std::shared_ptr<IGameObject>> gameObjects;
    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
    std::unique_ptr<ShaderProgram> defaultShaderProgram;
    std::unique_ptr<Camera> camera;
    GLFWwindow* window;
    ConfigReader* configReader; 
    std::shared_ptr<Input> input;               

    int width;
    int height;

    void updateGameObjects(float delta);
    void drawObjects();

public:
    Engine(GLFWwindow* window, ConfigReader* configReader);
    ~Engine() {}

    void init(const std::string& scenePath);
    void run();
    void shutdown();

    Camera* getCamera() const { return camera.get(); }
    double getDeltaTime();
    void addInput(std::shared_ptr<Input> input) { this->input = input; }
};

#endif
