#ifndef MESH_H
#define MESH_H

#include "IDrawableObject.h"
#include <vector>
#include <GL/glew.h>

using std::vector;

class Mesh : public IDrawableObject
{
public:
    Mesh() = default;
    Mesh(const vector<float>& points);
    ~Mesh();
    void draw() override;
    float* getArrayBuffer();
    void setup(ShaderProgram* shaderProgram = nullptr) override;

private:
    GLuint vao, vbo;
    vector<float> points;
    
};

#endif