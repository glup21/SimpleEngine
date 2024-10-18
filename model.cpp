#include "model.hpp"
#include <iostream>
#include <filesystem>
#include <memory> 
#include <unordered_map>

namespace fs = std::filesystem;
using std::unordered_map;

unordered_map<string, Texture> texturesLoaded;

Model::Model(string path, string ID, Transform transform, ShaderProgram* shaderProgram) 
    : directory(path), ID(ID), transform(transform), IDrawableObject(shaderProgram)
{
    setup();
}

void Model::setup()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(directory, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: assimp: " << importer.GetErrorString() << std::endl;
        return;
    }

    // Set directory for texture loading
    directory = directory.substr(0, directory.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(u_int64_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene));			
    }
    for(u_int64_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}  

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<u_int> indices;
    vector<Texture> textures;

    for(u_int64_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 vector;
        vec3 normal;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        if (mesh->HasNormals()) {
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;

            vertex.Normal = normal;
        } else {
            vertex.Normal = vec3(0.0f); // Optional: Set default normal
        }

        if (mesh->HasTextureCoords(0)) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f); // No texture coordinates
        }
        
        vertices.push_back(vertex);
    }

    for(u_int64_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(u_int64_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  

    // Process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }  

    Mesh res(vertices, indices, textures, shaderProgram);
    res.transform = transform;
    return res;
}  

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;

    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        string texturePath = directory + "/" + str.C_Str();
        
        if(texturesLoaded.find(texturePath) != texturesLoaded.end())
        {
            textures.push_back(texturesLoaded[texturePath]);
            continue; 
        }
        
        // Load texture
        int width, height, nrChannels;
        u_char* tmp = imageLoader.loadImage(texturePath, &height, &width, &nrChannels);

        if (tmp) {
            Texture texture(tmp, width, height, nrChannels, typeName);
            textures.push_back(texture);
            texturesLoaded[texturePath] = texture;
            std::cout << "Loaded texture from path: " << texturePath << "\n";
        } else {
            std::cerr << "Failed to load texture from path: " << texturePath << "\n";
        }
    }

    return textures;
}

void Model::update(float delta) 
{
   
}

void Model::draw()
{   
    for(u_int i = 0; i < meshes.size(); i++)
        meshes[i].draw();
}

Transform Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const Transform& newTransform) 
{
    transform = newTransform;

    for (Mesh& mesh : meshes) {
        mesh.transform = transform;
    }
}

void Model::setPosition(const vec3& newPosition) 
{
    vec3 currentPosition = transform.getPosition();
    vec3 delta = newPosition - currentPosition;
    transform.translate(delta.x, delta.y, delta.z);

    for (Mesh& mesh : meshes) {
        mesh.transform.translate(delta.x, delta.y, delta.z);
    }
}

void Model::setRotation(const vec3& rotationVec, const float& angle) 
{
    transform.rotate(angle, rotationVec.x, rotationVec.y, rotationVec.z);

    for (Mesh& mesh : meshes) {
        mesh.transform.rotate(angle, rotationVec.x, rotationVec.y, rotationVec.z);
    }
}

void Model::setScale(const vec3& newScale) 
{
    transform.scale(newScale.x, newScale.y, newScale.z);

    for (Mesh& mesh : meshes) {
        mesh.transform.scale(newScale.x, newScale.y, newScale.z);
    }
}

mat4 Model::getTransformMatrix() 
{
    return transform.getTransformMatrix();
}

