#include "model.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Model::Model(string path, string ID) : directory(path), ID(ID)
{

    loadModel(path);
    
}
void Model::loadModel(string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: assimp:" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::setup(Shader* shader)
{


}

void Model::update(float delta) 
{
    
    // float rotationSpeed = glm::radians(50.0f); 
    // float angle = rotationSpeed * delta;
    // quat incrementalRotation = glm::angleAxis(angle, vec3(0.0f, 1.0f, 0.0f)); 

    // // Apply the incremental rotation
    // addRotation(incrementalRotation);

    // addPosition(vec4(0, 0, 1, 1) * delta) ;
    // std::cout << transform.position.y << std::endl; 
}
void Model::draw(Shader* shader)
{
    mat4 transformMatrix = transform.getTransformMatrix();
  
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error after draw: " << err << std::endl;
    }
}
Transform Model::getTransform() const
{
    return transform;
}

void Model::setTransform(const Transform& transform)
{
    this->transform = transform;
}

void Model::setPosition(const vec3& newPosition)
{
    transform.position = newPosition;
}
void Model::setRotation(const quat& newRotation)
{
    transform.rotation = newRotation;
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
    vector<unsigned int> indices;
    vector<Texture> textures;

    for(u_int64_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;  

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
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
    // process indices
    for(u_int64_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material, 
                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }  

    return Mesh(vertices, indices, textures);
}  

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    std::cout << mat->GetTextureCount(type) << "\n";
    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        fs::path texturePath = fs::path(directory) / str.C_Str();
        Texture texture(typeName);
        std::cout << texturePath.string() << "\n";
        texture.loadFromFile(texturePath.string());
        textures.push_back(texture);
    }
    return textures;
}  