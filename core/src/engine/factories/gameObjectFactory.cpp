#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(ShaderProgram* defaultShaderProgram)
    : defaultShaderProgram(defaultShaderProgram), modelFactory(std::make_unique<ModelFactory>(defaultShaderProgram))
{

}

shared_ptr<Model> GameObjectFactory::createModel(string path, string ID)
{
    return modelFactory->createModel(path, ID);
}

shared_ptr<PointLight> GameObjectFactory::createPointLight()
{
    return std::make_shared<PointLight>();
}
shared_ptr<AmbientLight> GameObjectFactory::createAmbientLight()
{
    return std::make_shared<AmbientLight>();
}