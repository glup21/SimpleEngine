#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <string>
#include "transformComposite.hpp"  

using std::string;

class IGameObject
{
protected:
    TransformComposite transform;
    string ID;

public:
    virtual void update(float delta) = 0;
    virtual TransformComposite getTransform() const = 0;
    virtual void setTransform(const TransformComposite& transform) = 0;

    virtual void addPosition(const vec3& newPosition) = 0;
    virtual void addRotation(const vec3& rotationVec, const float& angle) = 0;
    virtual void addScale(const vec3& newScale) = 0;

    virtual mat4 getTransformMatrix() = 0;



};

#endif