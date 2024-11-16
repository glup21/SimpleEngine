#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include "IObjectFactory.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "modelLoader.hpp"
#include <unordered_map>
#include "modelLoader.hpp"
#include "shaderProgram.hpp"
#include <memory>
using std::unordered_map, std::string, std::shared_ptr, std::make_shared;

class ModelFactory : public IObjectFactory
{
private:

    unordered_map<string, ModelLoader::ModelData> cachedModels;
    ModelLoader modelLoader;
    ShaderProgram* defaultShaderProgram;

    shared_ptr<Model> makeModelFromData(ModelLoader::ModelData modelData, string ID, ShaderProgram* defaultShaderProgram);

public:
    ModelFactory(ShaderProgram* defaultShaderProgram);
    ~ModelFactory() = default;

    shared_ptr<Model> createModel(string path, string ID);

};

#endif