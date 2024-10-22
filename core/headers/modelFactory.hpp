#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include "IObjectFactory.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "modelLoader.hpp"
#include <unordered_map>

using std::unordered_map, std::string;

class ModelFactory : public IObjectFactory
{
private:

    unordered_map<string, Model> cachedModels;

public:
    ModelFactory() = default;
    ~ModelFactory();

    Model createModel(string path);

};

#endif