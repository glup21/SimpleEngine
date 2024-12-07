#include "modelFactory.hpp"
#include "Material.hpp"
#include "shaderFactory.hpp"
#include "MaterialFactory.hpp"

ModelFactory::ModelFactory() : modelLoader(ModelLoader())
{

}

shared_ptr<Model> ModelFactory::makeModelFromData(ModelLoader::ModelData modelData, int ID, int material)
{
    vector<Mesh> meshes;
    MaterialFactory& mf = MaterialFactory::getInstance();

    Material* mat = mf.getMaterialInstance(material);
    mat->addTextures(modelData.meshData[0].textures); // works only if all textures are the same for all meshes
    for(ModelLoader::MeshData meshData : modelData.meshData)
    {
        
        Mesh tmp(meshData.vertices, meshData.indices, mat);
        meshes.push_back(tmp);


    }
    return make_shared<Model>(ID, meshes);
}

shared_ptr<Model> ModelFactory::createModel(string path, int ID, int material)
{

    if(cachedModels.find(path) != cachedModels.end())
    {
        return makeModelFromData(cachedModels[path], ID, material);
    }

    ModelLoader::ModelData modelData = modelLoader.loadModel(path);

    cachedModels[path] = modelData;
    return makeModelFromData(modelData, modelID++, material);
        
}