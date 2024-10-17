#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/glm.hpp>
#include <iostream>

Camera::Camera(float x, float y, float z, float alpha, float fi) :
    position(x, y, z), alpha(alpha), fi(fi), upVector(0.0f, 0.0f, 1.0f)
{
    target.x=sin(alpha)* cos(fi);
    target.z=sin(alpha)* sin(fi);
    target.y=cos(alpha);
}

   /*    vec3 target, cameraPosition, forwardVector, upVector;
    float alpha = 0.0f;
    float fi = 0.0f;
    target.x=sin(alpha)* cos(fi);
    target.z=sin(alpha)* sin(fi);
    target.y=cos(alpha);

    cameraPosition = {0,0,0};
    forwardVector = cameraPosition + target;
    upVector = {0,0,1};

    mat4 viewMatrix = glm::lookAt(cameraPosition, forwardVector, upVector);
    mat4 projectionMatrix = glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 2.5f);

    shaderProgram->setMat4("projectionMatrix", projectionMatrix);
    shaderProgram->setMat4("viewMatrix", viewMatrix);*/

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + target, upVector);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(angle), ratio, nearDistance, farDistance);
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getForwardVector() const
{
    return position + target;
}

void Camera::forward()
{
    position += glm::normalize(target) * speed;
}

void Camera::left()
{
    position -= glm::normalize(glm::cross(glm::normalize(target), upVector)) * speed;
}

void Camera::backward()
{
    position -= glm::normalize(target) * speed;
}

void Camera::right()
{
    position += glm::normalize(glm::cross(glm::normalize(target), upVector)) * speed;
}

void Camera::changeTarget(float deltaX, float deltaY)
{
    fi += deltaX;
    alpha = glm::clamp(alpha + deltaY, -89.0f, 89.0f); 

    target.x=sin(alpha)* cos(fi);
    target.z=sin(alpha)* sin(fi);
    target.y=cos(alpha);

}
