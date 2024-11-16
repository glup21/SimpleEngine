#ifndef SCALE_H
#define SCALE_H

#include "transformComposite.hpp"

class Scale : public TransformComposite
{
private:
    mat4 transformMatrix;
    vec3 scale;

public:
    Scale() : scale(vec3(1.0f)), transformMatrix(mat4(1.0f)) {}
    Scale(vec3 scale) : scale(scale), transformMatrix(mat4(1.0f))
    {
        transformMatrix = glm::scale(mat4(1.0f), scale);
    }

    mat4 getTransformMatrix() override
    {
        return transformMatrix;
    }

    void setScale(vec3 newScale)
    {
        scale = newScale;
        transformMatrix = glm::scale(mat4(1.0f), scale);
    }
};

#endif
