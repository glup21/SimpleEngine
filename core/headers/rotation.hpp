#ifndef ROTATION_H
#define ROTATION_H

#include "transformComposite.hpp"

class Rotation : public TransformComposite
{
private:
    mat4 transformMatrix;
    vec3 rotationAxis;
    float angle;

public:
    Rotation() : rotationAxis(vec3(0.0f, 1.0f, 0.0f)), angle(0.0f), transformMatrix(mat4(1.0f)) {}
    Rotation(vec3 axis, float angle) : rotationAxis(axis), angle(angle), transformMatrix(mat4(1.0f))
    {
        transformMatrix = glm::rotate(mat4(1.0f), glm::radians(angle), axis);
    }

    mat4 getTransformMatrix() override
    {
        return transformMatrix;
    }

    void setRotation(vec3 axis, float newAngle)
    {
        rotationAxis = axis;
        angle = newAngle;
        transformMatrix = glm::rotate(mat4(1.0f), glm::radians(angle), rotationAxis);
    }
};

#endif
