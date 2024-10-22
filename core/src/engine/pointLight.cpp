#include "pointLight.hpp"
#include <cmath> 

PointLight::PointLight(ShaderProgram* shaderProgram) : shaderProgram(shaderProgram), time(0.0f)
{
}

void PointLight::addPosition(const vec3& newPosition) 
{
    Transform* newTransform = new Transform();
    newTransform->translate(newPosition.x, newPosition.y, newPosition.z);
    transform.addTransform(newTransform); 
}

mat4 PointLight::getTransformMatrix() 
{
    return transform.getTransformMatrix(); 
}

void PointLight::update(float delta)
{
    // Update the time variable
    time += delta;

    // Calculate the new position using sine and cosine functions
    float amplitude = 5.0f; // Amplitude of the sine wave
    float frequency = 1.0f; // Frequency of the sine wave
    float newX = amplitude * std::cos(frequency * time);
    float newY = amplitude * std::sin(frequency * time);

    // Update the position of the light
    vec3 currentPosition = vec3(getTransformMatrix()[3]);
    currentPosition.x = newX;
    currentPosition.y = newY;
    addPosition(currentPosition);

    // Set the LightPosition uniform in the shader program
    shaderProgram->setVec3("LightPosition", vec3(getTransformMatrix()[3]));

    // Output the full position of the light
    vec3 lightPosition = vec3(getTransformMatrix()[3]);
    std::cout << "Light Position: (" << lightPosition.x << ", " << lightPosition.y << ", " << lightPosition.z << ")" << std::endl;
}