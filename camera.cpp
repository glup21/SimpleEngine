#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/glm.hpp>
#include <iostream>

Camera::Camera(GLFWwindow* window, CameraSettings settings) :
    position(0,0,0), alpha(0.0f), fi(0.0f), upVector(0.0f, 1.0f, 0.0f), window(window), settings(settings)
{
    target.x = glm::cos(glm::radians(fi)) * glm::cos(glm::radians(alpha));
    target.y = glm::sin(glm::radians(alpha)); 
    target.z = glm::sin(glm::radians(fi)) * glm::cos(glm::radians(alpha));

    
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, glm::normalize(position + target), upVector);
}

glm::mat4 Camera::getProjectionMatrix() 
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    ratio = static_cast<float>(width)/static_cast<double>(height);
    return glm::perspective(glm::radians(settings.fov), ratio, settings.nearPlane, settings.farPlane);
}

glm::vec3 Camera::getPosition() const
{
    return position;
}

glm::vec3 Camera::getForwardVector() const
{
    return glm::normalize(position + target);
}

void Camera::move(vector<bool> keys, float deltaTime)
{

    vec3 forwardVector = getForwardVector();
    vec3 rightVector = getRightVector();
    vec3 movement(0.0f);

    if (keys[GLFW_KEY_W]) 
    { 
        movement += forwardVector;
    }
    if (keys[GLFW_KEY_S]) { 
        movement -= forwardVector;
    }
    if (keys[GLFW_KEY_A]) { 
        movement -= rightVector;
    }
    if (keys[GLFW_KEY_D]) { 
        movement += rightVector;
    }

    if (movement != glm::vec3(0.0f)) 
        movement = glm::normalize(movement);

    position += movement * settings.movingSpeed * deltaTime;
    std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;

}

void Camera::changeTarget(float deltaX, float deltaY, float delta)
{
    fi += deltaX * settings.lookSensitivity * delta;
    if (fi < 0) {
        fi += 360;
    } else if (fi >= 360) {
        fi -= 360; 
    }

    alpha = glm::clamp(alpha + (deltaY * settings.lookSensitivity * delta), -89.0f, 89.0f); 
    target.x = glm::cos(glm::radians(fi)) * glm::cos(glm::radians(alpha));
    target.y = glm::sin(glm::radians(alpha)); 
    target.z = glm::sin(glm::radians(fi)) * glm::cos(glm::radians(alpha));

    target = glm::normalize(target); 

}

vec3 Camera::getRightVector() const
{
    return glm::normalize(glm::cross(getForwardVector(), upVector));
}