#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

using glm::vec2;

class Input {
public:
    Input(GLFWwindow* window);

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    vec2 getMousePos();

private:
    void handleMouseMovement(double xpos, double ypos);
    vec2 mousePos;

    static Input* instance;
};

#endif