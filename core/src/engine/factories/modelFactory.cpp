#include "modelFactory.hpp"
#include "Material.hpp"
#include "shaderFactory.hpp"
#include "MaterialFactory.hpp"
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>

// Generate a unique key based on texture IDs
std::string generateTextureKey(const std::vector<Texture*>& textures)
{
    std::stringstream ss;
    for (auto texture : textures)
    {
        ss << texture->getID() << "_";
    }
    return ss.str();
}

ModelFactory::ModelFactory() : modelLoader(ModelLoader())
{
    // Initialize cachedModels and cachedMaterials here, if necessary
}

shared_ptr<Model> ModelFactory::makeModelFromData(ModelLoader::ModelData modelData, int ID, int material)
{
    vector<Mesh> meshes;
    MaterialFactory& mf = MaterialFactory::getInstance();

    // Move cachedMaterials here as a member variable (not local)
    if (cachedMaterials.empty()) {
        // Ensure that cachedMaterials is cleared when necessary (or manage the lifecycle).
    }

    for (ModelLoader::MeshData meshData : modelData.meshData)
    {
        Material* mat = nullptr;
        std::string textureKey = generateTextureKey(meshData.textures);

        if (cachedMaterials.find(textureKey) == cachedMaterials.end())
        {
            mat = mf.getMaterialInstance(material);
            mat->addTextures(meshData.textures);
            cachedMaterials[textureKey] = mat;
        }
        else
        {
            mat = cachedMaterials[textureKey];
        }

        Mesh tmp(meshData.vertices, meshData.indices, mat);
        meshes.push_back(tmp);
    }
    return make_shared<Model>(ID, meshes);
}

// This method appears to load and cache the model data by path
shared_ptr<Model> ModelFactory::createModel(string path, int ID, int material)
{
    if (cachedModels.find(path) != cachedModels.end())
    {
        return makeModelFromData(cachedModels[path], ID, material);
    }

    ModelLoader::ModelData modelData = modelLoader.loadModel(path);

    cachedModels[path] = modelData;
    return makeModelFromData(modelData, modelID++, material);
}
