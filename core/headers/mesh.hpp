#ifndef MESH_H
#define MESH_H

#include "IDrawableObject.hpp"
#include <vector>
#include <GL/glew.h>
#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "Material.hpp"

using std::vector;

class Mesh : public IDrawableObject
{
public:
    

    Mesh(vector<Vertex> vertices, vector<u_int> indices, Material* material);
    
    void draw() override;
    void setup() override;

    //Replace with TransformManager? Or inherit from abstract class ITransformable? 
    TransformComposite getTransform() const;
    void setTransform(const TransformComposite& transform);

    void addPosition(const vec3& newPosition);
    void addRotation(const vec3& rotationVec, const float& angle);
    void addScale(const vec3& newScale);

    mat4 getTransformMatrix();

private:
    TransformComposite transform;
    GLuint VAO, VBO, EBO;
    vector<Vertex> vertices;
    vector<u_int> indices;
    Material* material;
};

#endif