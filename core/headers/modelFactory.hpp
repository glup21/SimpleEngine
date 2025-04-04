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
    unordered_map<string, Material*> cachedMaterials;  

    ModelLoader modelLoader;

    int modelID = 0;

    shared_ptr<Model> makeModelFromData(ModelLoader::ModelData modelData, int ID, int material);

public:
    ModelFactory();
    ~ModelFactory() = default;

    shared_ptr<Model> createModel(string path, int ID, int material);

};

#endif