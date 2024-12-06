#include "modelFactory.hpp"

ModelFactory::ModelFactory(ShaderProgram* defaultShaderProgram) : defaultShaderProgram(defaultShaderProgram), modelLoader(ModelLoader())
{

}

shared_ptr<Model> ModelFactory::makeModelFromData(ModelLoader::ModelData modelData, int ID, ShaderProgram* defaultShaderProgram)
{
    vector<Mesh> meshes;
    for(ModelLoader::MeshData meshData : modelData.meshData)
    {
        Mesh tmp(meshData.vertices, meshData.indices, meshData.textures, defaultShaderProgram);
        meshes.push_back(tmp);


    }
    return make_shared<Model>(ID, defaultShaderProgram, meshes);
}

shared_ptr<Model> ModelFactory::createModel(string path, int ID)
{

    if(cachedModels.find(path) != cachedModels.end())
    {
        return makeModelFromData(cachedModels[path], ID, defaultShaderProgram);
    }

    ModelLoader::ModelData modelData = modelLoader.loadModel(path);

    cachedModels[path] = modelData;
    return makeModelFromData(modelData, modelID++, defaultShaderProgram);
}