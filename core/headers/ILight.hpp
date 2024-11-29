#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "IGameObject.hpp"
#include "glm/glm.hpp"

using glm::vec4;

class ILight : public IGameObject 
{
protected:
    vec4 color;
    int type;

public:
    ILight(vec4 color = vec4(1.0f), int type = 1) : color(color), type(type) {}  
    virtual ~ILight() = default;

    virtual glm::mat4 getTransformMatrix() = 0;

    TransformComposite getTransform() const override { return transform; }  
    void setTransform(const TransformComposite& newTransform) override { transform = newTransform; }
    void addPosition(const glm::vec3& newPosition) override {}

    vec4 getColor() const { return color; }
    void setColor(const vec4& newColor) { color = newColor; }

    int getType() const { return type; }
};

#endif
