#include "mesh.hpp"
#include <iostream>
#include "position.hpp"   
#include "rotation.hpp"   
#include "scale.hpp"      

Mesh::Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture*> textures, ShaderProgram* shaderProgram) :
    vertices(vertices), indices(indices), textures(textures), IDrawableObject(shaderProgram, 0)
{
    setup();
}

void Mesh::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
    shaderProgram->link();
}

void Mesh::draw()
{
    glm::mat4 transformMatrix = transform.getTransformMatrix();
    shaderProgram->setMat4("transform", transformMatrix);

    shaderProgram->setInt("textureImage", 0);
    textures[0]->bind(0);

    shaderProgram->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

TransformComposite Mesh::getTransform() const
{
    return transform;
}

void Mesh::setTransform(const TransformComposite& transform)
{
    this->transform = transform;
}

void Mesh::addPosition(const glm::vec3& newPosition) 
{
    Position* position = new Position(newPosition);
    transform.addTransform(position);
}

void Mesh::addRotation(const glm::vec3& rotationVec, const float& angle) 
{
    Rotation* rotation = new Rotation(rotationVec, angle);
    transform.addTransform(rotation);
}

void Mesh::addScale(const glm::vec3& newScale) 
{
    Scale* scale = new Scale(newScale);
    transform.addTransform(scale);
}

glm::mat4 Mesh::getTransformMatrix() 
{
    return transform.getTransformMatrix(); 
}
