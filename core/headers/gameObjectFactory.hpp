#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

#include "IObjectFactory.hpp"
#include "modelFactory.hpp"
#include <memory>
#include "shaderProgram.hpp"
#include "model.hpp"
#include "pointLight.hpp"
#include "AmbientLight.hpp"

using std::unique_ptr, std::shared_ptr;

class GameObjectFactory : public IObjectFactory
{
private:
    unique_ptr<ModelFactory> modelFactory;
    ShaderProgram* defaultShaderProgram;

public:
    GameObjectFactory(ShaderProgram* defaultShaderProgram);
    ~GameObjectFactory() = default;

    shared_ptr<Model> createModel(string path, string ID); //other ways of creation implement later
    shared_ptr<PointLight> createPointLight();
    shared_ptr<AmbientLight> createAmbientLight();
};

#endif