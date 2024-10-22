#ifndef MODEL_H
#define MODEL_H

#include "mesh.hpp"
#include "shader.hpp"
#include "IGameObject.hpp"
#include "IDrawableObject.hpp"
#include <vector>

using std::vector;

class Model : public IGameObject, public IDrawableObject
{
public:
    Model(string ID, ShaderProgram* shaderProgram, vector<Mesh> meshes);

    void setup() override;
    void draw() override;
    void update(float delta) override;

    //just gets transform
    TransformComposite getTransform() const override;
    void setTransform(const TransformComposite& transform) override;

    void addPosition(const vec3& newPosition) override;
    void addRotation(const vec3& rotationVec, const float& angle) override;
    void addScale(const vec3& newScale) override;

    //returns overall transform, with all children
    mat4 getTransformMatrix() override;
private:
    string ID;
    vector<Mesh> meshes;
    string directory;
    TransformComposite transform;

};

#endif