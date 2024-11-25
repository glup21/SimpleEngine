#include "input.hpp"
#include <glm/glm.hpp>

Input* instance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    instance->onKeyCallback(key, action);
}

void window_focus_callback(GLFWwindow* window, int focused) 
{
    instance->onWindowFocus(focused);
}

Input::Input(GLFWwindow* window, Application* application, Engine* engine)
    : window(window), keys(vector<bool>(500, false)), application(application), engine(engine), camera(engine->getCamera())
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);

    instance = this;
}

void Input::setEngine(Engine* newEngine) 
{
    this->engine = newEngine;
    camera = engine->getCamera();
}

void Input::onKeyCallback(int key, int action) 
{
    if (action == GLFW_PRESS) 
    {
        if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
            // Causes segmentation fault, fix later 
            //application->loadScene(key - GLFW_KEY_0 - 1);
        }
        keys[key] = true;

    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}


void Input::onWindowFocus(int focused) 
{
    isWindowFocused = (focused == GLFW_TRUE);
}
void Input::updateInput(const double& deltaTime)
{
    if(isWindowFocused)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        vec2 mouseDelta(width / 2.0 - xpos, height / 2.0 - ypos);

        if (isWindowFocused && glm::length(mouseDelta) > 0.01f) {
            mouseDelta = glm::normalize(mouseDelta);
            camera->changeTarget(-mouseDelta.x, mouseDelta.y, deltaTime);
        }
        glfwSetCursorPos(window, width / 2.0, height / 2.0);

        camera->changeTarget(-mouseDelta.x, mouseDelta.y, deltaTime);
        camera->move(keys, deltaTime);
    }


}