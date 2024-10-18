#ifndef CAMERA_H
#define CAMERA_H

#include "shaderProgram.hpp"
#include <GLFW/glfw3.h>
#include "cameraSettings.hpp"
using glm::vec3, glm::mat4;

class Camera
{
private:
    ShaderProgram* shaderProgram;
	vec3 position;
	vec3 upVector;
    vec3 target;
    vec3 currentTarget;
    GLFWwindow* window;

    float ratio;
    float alpha;
    float fi;

    CameraSettings settings;

public:
    Camera(GLFWwindow* window, CameraSettings settings);
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix();
    vec3 getPosition() const;
    vec3 getForwardVector() const;
    vec3 getRightVector() const;

    void move(vector<bool> keys, float deltaTime);
    void changeTarget(float deltaX, float deltaY, float delta);
};

#endif