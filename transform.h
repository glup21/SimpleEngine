#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

using glm::vec3, glm::vec4, glm::mat4, glm::quat;

struct Transform
{

    vec3 position;
    quat rotation;
    vec3 scale;
    Transform()
            : position(0.0f, 0.0f, 0.0f), 
            rotation(1.0f, 0.0f, 0.0f, 0.0f), 
            scale(1.0f, 1.0f, 1.0f) {}

    

    mat4 getTransformMatrix() const
    {
        mat4 matrix = mat4(1.0f);
        matrix = glm::translate(matrix, position);
        matrix *= glm::mat4_cast(rotation);
        matrix = glm::scale(matrix, scale);

        return matrix;
    }
};

#endif