#include "AmbientLight.hpp"
#include "position.hpp"

AmbientLight::AmbientLight(vec4 color)
    : ILight(color, 0) // Type 0 for ambient light
{
    notifyObservers();
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
    //notifyObservers();
}
