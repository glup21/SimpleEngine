#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(ShaderProgram* defaultShaderProgram)
    : defaultShaderProgram(defaultShaderProgram), modelFactory(std::make_unique<ModelFactory>(defaultShaderProgram))
{

}

shared_ptr<Model> GameObjectFactory::createModel(string path, string ID)
{
    return modelFactory->createModel(path, ID);
}

shared_ptr<PointLight> GameObjectFactory::createLight()
{
    return std::make_shared<PointLight>();
}