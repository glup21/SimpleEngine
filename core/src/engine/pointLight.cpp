#include "pointLight.hpp"
#include "position.hpp"


PointLight::PointLight(vec4 color, float distance)
    : ILight(color, 1), distance(distance) 
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
    //notifyObservers();
}


