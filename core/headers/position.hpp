#ifndef POSITION_H
#define POSITION_H

#include "transformComposite.hpp"

class Position : public TransformComposite
{
private:
    mat4 transformMatrix;
    vec3 position= vec3(0.0f);

public: 
    Position() :  position(vec3(1.0f)), transformMatrix(mat4(1.0f)) {}
    ~Position() = default;

    Position(vec3 position) : position(position), transformMatrix(mat4(1.0f)) 
    {
        transformMatrix = glm::translate(transformMatrix, position);
    }

    vec3 getPosition() { return position; }

    mat4 getTransformMatrix() override
    {
        return transformMatrix;
    }

};

#endif 