#ifndef MESH_H
#define MESH_H

#include "IDrawableObject.h"
#include <vector>
#include <GL/glew.h>

class Mesh : public IDrawableObject
{
public:
    Mesh() = default;
    Mesh(const std::vector<float>& points);
    ~Mesh();
    void draw() override;
    float* getArrayBuffer();
    void setup() override;

private:
    GLuint vao, vbo;
    std::vector<float> points;
    
};

#endif