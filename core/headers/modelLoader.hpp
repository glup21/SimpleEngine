#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "ILoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "imageLoader.hpp"
#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp> 
#include "texture.hpp"
#include "mesh.hpp"
#include "imageLoader.hpp"
#include <unordered_map>

using std::vector, glm::vec3, std::unordered_map;

class ModelLoader
{
public:
    struct MeshData
    {
        vector<Vertex> vertices;
        vector<u_int> indices;
        vector<Texture*> textures;
    };
    struct ModelData
    {
        vector<MeshData> meshData;
    };

    ModelLoader();
    ModelData loadModel(string path);

private:
    ImageLoader imageLoader;
    unordered_map<string, Texture*> loadedTextures;

    void processNode(aiNode* node, const aiScene* scene, ModelData& modelData, string path);
    void processMesh(aiMesh* mesh, const aiScene* scene, ModelData& modelData, string path);
    vector<Texture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, string path);

};

#endif