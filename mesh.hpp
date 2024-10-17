#ifndef MESH_H
#define MESH_H

#include "IDrawableObject.hpp"
#include <vector>
#include <GL/glew.h>
#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "transform.hpp"

using std::vector;

class Mesh : public IDrawableObject
{
public:
    Transform transform;

    Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture> textures);
    
    void draw(Shader* shader = nullptr) override;
    void setup(Shader* shader = nullptr) override;

private:
    GLuint VAO, VBO, EBO;
    vector<Vertex> vertices;
    vector<u_int> indices;
    vector<Texture> textures;

};

#endif