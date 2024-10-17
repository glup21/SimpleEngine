#include "model.hpp"
#include <iostream>
#include <filesystem>
#include <memory> 
#include <unordered_map>
namespace fs = std::filesystem;
using std::unordered_map;
unordered_map<string, Texture> texturesLoaded;

Model::Model(string path, string ID, Transform transform) : directory(path), ID(ID), transform(transform)
{

    //loadModel(path);
    setup();
    
    
}

void Model::setup(Shader* shader)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(directory, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: assimp:" << importer.GetErrorString() << std::endl;
        return;
    }
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
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;  

        if(mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
        
        vertices.push_back(vertex);
    }

    for(u_int64_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(u_int64_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }  

    Mesh res(vertices, indices, textures);
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
        bool skip = false;
        string texturePath = directory + "/" + str.C_Str();
        for(unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if(texturesLoaded.find(texturePath) != texturesLoaded.end())
            {
                textures.push_back(texturesLoaded[texturePath]);
                skip = true; 
                break;
            }
        }
        
        if(!skip)
        {
            int width, height, nrChannels;
            u_char* tmp = imageLoader.loadImage(texturePath, &height, &width, &nrChannels);

            Texture texture(tmp, width, height, nrChannels, typeName);

            std::cout << "Loaded texture from path: " << texturePath << "\n";
            textures.push_back(texture);

            texturesLoaded[texturePath] = texture;
        }

    }

    return textures;
}

void Model::update(float delta) 
{
    
}
void Model::draw(Shader* shader)
{   
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);

    
}
Transform Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const Transform& transform)
{
    Transform tmp = transform;
    tmp.rotation = glm::normalize(tmp.rotation);
    this->transform = tmp;
}

void Model::setPosition(const vec3& newPosition)
{
    transform.position = newPosition;
}
void Model::setRotation(const quat& newRotation)
{
    transform.rotation = glm::normalize(newRotation);
}
void Model::setScale(const vec3& newScale)
{
    transform.scale = newScale;
}

mat4 Model::getTransformMatrix() const
{
    return transform.getTransformMatrix();
}

void Model::addPosition(const vec3& addPosition)
{
    transform.position += addPosition;
}

void Model::addRotation(const quat& addRotation)
{
    transform.rotation = glm::normalize(addRotation * transform.rotation);
}


