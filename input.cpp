#include "input.hpp"

Input* Input::instance = nullptr;

Input::Input(GLFWwindow* window) 
{
    instance = this;
    glfwSetCursorPosCallback(window, mouseCallback);
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos) 
{
    if (instance) {
        instance->handleMouseMovement(xpos, ypos);
    }
}

void Input::handleMouseMovement(double xpos, double ypos) 
{
    
}
vec2 Input::getMousePos()
{
    return mousePos;
}