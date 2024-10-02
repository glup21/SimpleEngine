#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "shader.h"
#include "IGameObject.h"
#include "IDrawableObject.h"
#include "shaderProgram.h"

class Model : public IGameObject, public IDrawableObject
{
    Mesh* mesh;
    Shader* shader;
    Transform transform;
    //ShaderProgram* shaderProgram;


public:
    Model() = default;
    Model(Mesh* m, Shader* s = nullptr);
    ~Model() = default;

    Mesh* getMesh();
    Shader* getShader();


    void setup(ShaderProgram* shaderProgram) override;
    void draw() override;
    void update() override;
    Transform getTransform() override;
    void setTransform(const Transform& transform) override;

};

#endif