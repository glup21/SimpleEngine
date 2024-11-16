#include "modelLoader.hpp"
#include "defaultAssets.hpp"

ModelLoader::ModelLoader() {}

ModelLoader::ModelData ModelLoader::loadModel(string path)
{

    Assimp::Importer importer;
    ModelData res;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: assimp: " << importer.GetErrorString() << std::endl;
        return res;
    }

    // Set path for texture loading
    path = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene, res, path);

    return res;

}


void ModelLoader::processNode(aiNode* node, const aiScene* scene, ModelData& modelData, string path)
{
    for(u_int64_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        processMesh(mesh, scene, modelData, path);			
    }
    for(u_int64_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, modelData, path);
    }
}  

void ModelLoader::processMesh(aiMesh* mesh, const aiScene* scene, ModelData& modelData, string path)
{
    vector<Vertex> vertices;
    vector<u_int> indices;
    vector<Texture*> textures;

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
            vertex.Normal = vec3(1.0f); 
        }

        if (mesh->HasTextureCoords(0)) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        
        vertices.push_back(vertex);
    }


    for(u_int64_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(u_int64_t j = 0; j < face.mNumIndices; j++)
        {
            if (!mesh->HasNormals())
            {
                vec3 v0 = vertices[face.mIndices[0]].Position;
                vec3 v1 = vertices[face.mIndices[1]].Position;
                vec3 v2 = vertices[face.mIndices[2]].Position;
                vec3 edge1 = v1 - v0;
                vec3 edge2 = v2 - v0;
                vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));
                vertices[face.mIndices[0]].Normal += faceNormal;
                vertices[face.mIndices[1]].Normal += faceNormal;
                vertices[face.mIndices[2]].Normal += faceNormal;

            }
            indices.push_back(face.mIndices[j]);

        }
    }

    // Process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        
        vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", path);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }  

    MeshData md{vertices, indices, textures};
    modelData.meshData.push_back(md);
}  

vector<Texture*> ModelLoader::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, string path)
{
    DefaultAssets defaultAssets;
    string defaultTexturePath = defaultAssets.defaultTexturePath;
    vector<Texture*> textures;

    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
    
        string texturePath = path + "/" + str.C_Str();
        
        if(loadedTextures.find(texturePath) != loadedTextures.end())
        {
            textures.push_back(loadedTextures[texturePath]);
            continue; 
        }
        
        // Load texture
        int width, height, nrChannels;
        u_char* tmp = imageLoader.loadImage(texturePath, &height, &width, &nrChannels);

        if (tmp) 
        {
            //Texture texture(tmp, width, height, nrChannels, typeName);
            Texture* texture = new Texture(tmp, width, height, nrChannels, typeName);
            textures.push_back(texture);
            loadedTextures[texturePath] = texture;
            std::cout << "Loaded texture from path: " << texturePath << "\n";
        } 
        else 
        {
            std::cerr << "Failed to load texture from path: " << texturePath << "\n";
            std::cerr << "Using default texture instead.\n";

            texturePath = path + "/" + defaultTexturePath.c_str();
            tmp = imageLoader.loadImage(texturePath, &height, &width, &nrChannels);

            Texture* texture = new Texture(tmp, width, height, nrChannels, typeName);
            textures.push_back(texture);
            loadedTextures[texturePath] = texture;
            std::cout << "Loaded texture from path: " << texturePath << "\n";
        }
    }

    if(textures.size() == 0)
    {
        string texturePath = path + "/" + defaultTexturePath.c_str();
        std::cout << "No textures on model! Replacing with default texture.\n";
        std::cout << "Default texture path: " << texturePath << "\n";
        
        int width, height, nrChannels;
        u_char* tmp = imageLoader.loadImage(texturePath, &height, &width, &nrChannels);

        if (tmp) 
        {
            Texture* texture = new Texture(tmp, width, height, nrChannels, typeName);
            textures.push_back(texture);
            loadedTextures[texturePath] = texture;
            std::cout << "Loaded texture from path: " << texturePath << "\n";
        } 
    }

    return textures;
}
