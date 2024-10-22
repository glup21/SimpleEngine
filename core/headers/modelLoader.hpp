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

using std::vector, glm::vec3;

class ModelLoader
{
public:
    struct MeshData
    {
        vector<Vertex> vertices;
        vector<u_int> indices;
    };
    struct ModelData
    {
        vector<MeshData> meshData;
        vector<Texture> textures;
    };

    ModelLoader(ShaderProgram* shaderProgram);
    ModelData loadModel(string path);

private:
    ImageLoader imageLoader;

    void processNode(aiNode* node, const aiScene* scene, ModelData& modelData);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, ModelData& modelData);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

};

#endif MESH_LOADER_H