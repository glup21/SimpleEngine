#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture> textures, ShaderProgram* shaderProgram) :
    vertices(vertices), indices(indices), textures(textures), IDrawableObject(shaderProgram)
{
    setup();
}

void Mesh::setup()
{

    glGenVertexArrays(1, &VAO); //Create VAO, VBO, EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VAO and VBO

    //move date from vertices vector to VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), 
        &vertices[0], GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //Bind EBO
    //Move indices to EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int), 
        &indices[0], GL_STATIC_DRAW);

    //defines array of VAO for vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    //defines array of VAO for normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    //defines array of VAO for texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    shaderProgram->link();
}

void Mesh::draw()
{
    mat4 transformMatrix = transform.getTransformMatrix();
    shaderProgram->setMat4("transform", transformMatrix);

    vec3 target, cameraPosition, forwardVector, upVector;
    float alpha = 0.0f;
    float fi = 0.0f;
    target.x=sin(alpha)* cos(fi);
    target.z=sin(alpha)* sin(fi);
    target.y=cos(alpha);

    cameraPosition = {0,0,0};
    forwardVector = cameraPosition + target;
    upVector = {0,0,1};

    mat4 viewMatrix = glm::lookAt(cameraPosition, forwardVector, upVector);
    mat4 projectionMatrix = glm::perspective(70.0f, 16.0f/9.0f, 0.1f, 2.5f);

    shaderProgram->setMat4("projectionMatrix", projectionMatrix);
    shaderProgram->setMat4("viewMatrix", viewMatrix);

    shaderProgram->setInt("textureImage", 0);
    textures[0].bind(0);

    shaderProgram->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}