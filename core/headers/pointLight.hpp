#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "transformComposite.hpp"
#include "IGameObject.hpp"
#include "shaderProgram.hpp"

using glm::vec3, glm::mat4;

class PointLight : public IGameObject, public Subject {
private:
    TransformComposite transform;
    vec3 color;
    float brightness;
    int type;

public:
    PointLight(vec3 color = vec3(1.0f), float brightness = 1.0f);
    ~PointLight() = default;

    void addPosition(const vec3& newPosition);
    mat4 getTransformMatrix();

    void update(float delta) override;

    TransformComposite getTransform() const { return transform; }
    void setTransform(const TransformComposite& transform) { this->transform = transform; }
    //to make compiler shut up
    void addRotation(const vec3& rotationVec, const float& angle) override {}
    void addScale(const glm::vec3& newScale) override {}

    vec3 getColor() const { return color; }
    float getBrightness() const { return brightness; }
    int getType() const { return type; }

    void setColor(const vec3& newColor) { color = newColor; notifyObservers(); }
    void setBrightness(float newBrightness) { brightness = newBrightness; notifyObservers(); }
};

#endif
