#include "pointLight.hpp"
#include "position.hpp"

PointLight::PointLight(vec3 color, float brightness)
    : color(color), brightness(brightness), type(1) 
{
    notifyObservers();
}

void PointLight::addPosition(const vec3& newPosition)
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);
    notifyObservers();
}

mat4 PointLight::getTransformMatrix()
{
    return transform.getTransformMatrix();
}

void PointLight::update(float delta)
{
    notifyObservers();
}
