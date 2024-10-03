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

void Mesh::setup(ShaderProgram* shaderProgram)
{
    // Generate and bind the VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBindBuffer: " << error << std::endl;
    }

    // Upload the vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBufferData: " << error << std::endl;
    }

    // Generate and bind the VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBindVertexArray: " << error << std::endl;
    }

    // Enable vertex attributes
    glEnableVertexAttribArray(0);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glEnableVertexAttribArray: " << error << std::endl;
    }

    // Bind the VBO again (VAO should remember this binding)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBindBuffer (second time): " << error << std::endl;
    }

    // Define the vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glVertexAttribPointer: " << error << std::endl;
    }

    // Unbind the VAO to prevent accidental modification
    glBindVertexArray(0);

    // Check for OpenGL errors
    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after glBindVertexArray(0): " << error << std::endl;
    }
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