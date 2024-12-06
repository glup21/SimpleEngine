#include "SpotLight.hpp"
#include "position.hpp"
#include "rotation.hpp"

SpotLight::SpotLight(vec4 color, float distance, float angle )
    : ILight(color, 2), distance(distance), angle(angle)  
{
    notifyObservers();
}

void SpotLight::addPosition(const vec3& newPosition)
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);
    notifyObservers();
}

void SpotLight::addRotation(const glm::vec3& rotationVec, const float& angle) 
{
    Rotation* rotation = new Rotation(rotationVec, angle);
    transform.addTransform(rotation);
    notifyObservers();
}

mat4 SpotLight::getTransformMatrix()
{
    return transform.getTransformMatrix();  
}


void SpotLight::update(float delta)
{

    // notifyObservers();
}

