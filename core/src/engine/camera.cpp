#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

Camera::Camera(GLFWwindow* window, CameraSettings settings) :
    upVector(0.0f, 1.0f, 0.0f), window(window), settings(settings)
{
    // Initialize the target direction (looking along the -Z axis by default)
    target = vec3(0.0f, 0.0f, -1.0f);
}

glm::mat4 Camera::getViewMatrix() 
{
    vec3 position = transform.getTransformMatrix()[3];  // Extract position from the transform matrix
    return glm::lookAt(position, position + getForwardVector(), upVector);
}

glm::mat4 Camera::getProjectionMatrix()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    ratio = static_cast<float>(width) / static_cast<float>(height);
    return glm::perspective(glm::radians(settings.fov), ratio, settings.nearPlane, settings.farPlane);
}

glm::vec3 Camera::getPosition() 
{
    // Extract the translation component from the composite transform
    return vec3(transform.getTransformMatrix()[3]);
}

glm::vec3 Camera::getForwardVector() 
{
    // Forward vector based on the current target and transformation
    return glm::normalize(transform.getTransformMatrix() * vec4(target, 0.0f));
}

glm::vec3 Camera::getRightVector() 
{
    return glm::normalize(glm::cross(getForwardVector(), upVector));
}

void Camera::move(const vector<bool>& keys, const float& deltaTime)
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

    addPosition(movement * settings.movingSpeed * deltaTime);
}

void Camera::changeTarget(const float& deltaX, const float& deltaY, const float& delta)
{
    float fi = glm::degrees(atan2(target.z, target.x));
    float alpha = glm::degrees(asin(target.y));

    fi += deltaX * settings.lookSensitivity * delta;
    alpha = glm::clamp(alpha + deltaY * settings.lookSensitivity * delta, -89.0f, 89.0f);

    target.x = glm::cos(glm::radians(fi)) * glm::cos(glm::radians(alpha));
    target.y = glm::sin(glm::radians(alpha));
    target.z = glm::sin(glm::radians(fi)) * glm::cos(glm::radians(alpha));

    target = glm::normalize(target);
}


void Camera::update(const vector<bool>& keys, const float& deltaX, const float& deltaY,  const float& deltaTime)
{

    changeTarget(deltaX, deltaY, deltaTime);
    move(keys, deltaTime);


    notifyObservers();
    
}

TransformComposite Camera::getTransform() const
{
    return transform;
}

void Camera::setTransform(const Transform& newTransform)
{
    transform = newTransform;
}

void Camera::addPosition(const vec3& newPosition)
{
    Transform* translationTransform = new Transform();
    translationTransform->translate(newPosition.x, newPosition.y, newPosition.z);
    transform.addTransform(translationTransform);  
}

void Camera::addRotation(const vec3& rotationVec, const float& angle)
{
    Transform* rotationTransform = new Transform();
    rotationTransform->rotate(angle, rotationVec.x, rotationVec.y, rotationVec.z);
    transform.addTransform(rotationTransform);  
}
