#ifndef CAMERA_H
#define CAMERA_H

#include "shaderProgram.hpp"

using glm::vec3, glm::mat4;

class Camera
{
private:
    ShaderProgram* shaderProgram;
	vec3 position;
	vec3 upVector;
    vec3 target;
	vec3 forwardVector;

    float ratio = 16.0f/9.0f;
    float angle = 70.0f;
    float nearDistance = 0.01f;
    float farDistance = 100.0f;
    float speed = 0.1f;
    float alpha;
    float fi;

public:
    Camera(float x = 0.0f, float y = 0.0f, float z = 0.0f, float alpha = 0.0f, float fi = 0.0f);
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    vec3 getPosition() const;
    vec3 getForwardVector() const;

    void forward();
	void left();
	void backward();
	void right();
    void changeTarget(float deltaX, float deltaY);
};

#endif