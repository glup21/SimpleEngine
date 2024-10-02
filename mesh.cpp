#include "mesh.h"

Mesh::Mesh(const std::vector<float>& points) : points(points)
{
    //setupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::setup(ShaderProgram* shaderProgram)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::draw() 
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, points.size() / 3);
    glBindVertexArray(0);
}

float* Mesh::getArrayBuffer()
{
    return points.data();
}