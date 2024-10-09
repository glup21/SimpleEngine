#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(vector<Vertex> vertices, vector<u_int> indices, vector<Texture> textures) :
    vertices(vertices), indices(indices), textures(textures)
{
    setup();
}

void Mesh::setup(Shader* shader)
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
}

void Mesh::draw(Shader* shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].getID());
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



// Mesh::Mesh(const std::vector<float>& points) : points(points)
// {
//     setup();
// }

// Mesh::~Mesh()
// {
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
// }

// void Mesh::setup(ShaderProgram* shaderProgram) //REWRITE LATER
// {

//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
    
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);
//     glEnableVertexAttribArray(0);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

//     //glBindVertexArray(0);
// }


// void Mesh::draw() 
// {
//     if (VAO == 0) {
//         std::cerr << "Error: VAO is not initialized." << std::endl;
//         return;
//     }
//     glBindVertexArray(VAO);
//     glDrawArrays(GL_TRIANGLES, 0, points.size() / 3);
//     glBindVertexArray(0);

//     GLenum error = glGetError();
//         if (error != GL_NO_ERROR) {
//             std::cerr << "OpenGL error in draw: " << error << std::endl;
//         }
    
// }

// float* Mesh::getArrayBuffer()
// {
//     return points.data();
// }