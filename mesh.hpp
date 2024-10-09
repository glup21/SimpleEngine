#ifndef MESH_H
#define MESH_H

#include "IDrawableObject.hpp"
#include <vector>
#include <GL/glew.h>
#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"

using std::vector;

class Mesh : public IDrawableObject
{
public:
    vector<Vertex> vertices;
    vector<u_int> indices;
    vector<Texture> textures;
    

    Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture> textures);
    
    void draw(Shader* shader = nullptr) override;
    void setup(Shader* shader = nullptr) override;
    //float* getArrayBuffer();

private:
    GLuint VAO, VBO, EBO;

};

#endif