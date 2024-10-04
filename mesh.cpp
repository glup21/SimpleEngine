#include "mesh.h"
#include <iostream>
Mesh::Mesh(const std::vector<float>& points) : points(points)
{
    setup();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::setup(ShaderProgram* shaderProgram) //REWRITE LATER
{

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //glBindVertexArray(0);
}


void Mesh::draw() 
{
    if (VAO == 0) {
        std::cerr << "Error: VAO is not initialized." << std::endl;
        return;
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, points.size() / 3);
    glBindVertexArray(0);

    GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error in draw: " << error << std::endl;
        }
    
}

float* Mesh::getArrayBuffer()
{
    return points.data();
}