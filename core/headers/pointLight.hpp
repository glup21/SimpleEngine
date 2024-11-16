#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "transformComposite.hpp"
#include "IGameObject.hpp"
#include "shaderProgram.hpp"

using glm::vec3, glm::mat4;

class PointLight : public IGameObject, public Subject {
private:
    TransformComposite transform;

public:
    PointLight();
    ~PointLight() = default;

    void addPosition(const vec3& newPosition);
    mat4 getTransformMatrix();

    void update(float delta) override;

    TransformComposite getTransform() const { return transform; }
    void setTransform(const TransformComposite& transform) { this->transform = transform; }

    void addRotation(const vec3& rotationVec, const float& angle) {}
    void addScale(const vec3& newScale) {}
};

#endif
