#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "transform.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class IGameObject
{
protected:
    Transform transform;
    string ID;

public:
    virtual void update(float delta) = 0;
    virtual Transform getTransform() const = 0;
    virtual void setTransform(const Transform& transform) = 0;

    virtual void setPosition(const vec3& newPosition) = 0;
    virtual void setRotation(const vec3& rotationVec, const float& angle) = 0;
    virtual void setScale(const vec3& newScale) = 0;

    virtual mat4 getTransformMatrix() = 0;



};

#endif