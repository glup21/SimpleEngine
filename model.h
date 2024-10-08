#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shader.h"
#include "IGameObject.h"
#include "IDrawableObject.h"
#include "shaderProgram.h"
#include "material.hpp"

class Model : public IGameObject, public IDrawableObject
{
    Mesh* mesh;
    Transform transform;
    ShaderProgram* shaderProgram;


public:
    Model(Mesh* m, ShaderProgram* sp);
    ~Model() = default;

    Mesh* getMesh();

    void setup(ShaderProgram* sP = nullptr) override;
    void draw() override;
    void update(float delta) override;
    Transform getTransform() const override;
    void setTransform(const Transform& transform) override;

    void setPosition(const vec3& newPosition) override;
    void setRotation(const quat& newRotation) override;
    void setScale(const vec3& newScale) override;

    void addPosition(const vec3& addPosition) override;
    void addRotation(const quat& addRotation) override;

    mat4 getTransformMatrix() const override;

};

#endif