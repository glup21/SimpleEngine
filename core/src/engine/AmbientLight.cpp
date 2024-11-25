#include "AmbientLight.hpp"
#include "position.hpp"

AmbientLight::AmbientLight(vec3 color, float brightness)
    : color(color), brightness(brightness), type(0) // Type 0 for ambient light
{
}

void AmbientLight::addPosition(const vec3& newPosition)
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);
    notifyObservers();
}

mat4 AmbientLight::getTransformMatrix()
{
    return transform.getTransformMatrix();
}

void AmbientLight::update(float delta)
{
    
}
