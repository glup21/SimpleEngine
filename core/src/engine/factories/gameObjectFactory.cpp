#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(ShaderProgram* defaultShaderProgram)
    : defaultShaderProgram(defaultShaderProgram), modelFactory(std::make_unique<ModelFactory>(defaultShaderProgram))
{

}

shared_ptr<Model> GameObjectFactory::createModel(string path, string ID)
{
    return modelFactory->createModel(path, ID);
}

shared_ptr<PointLight> GameObjectFactory::createPointLight(
        glm::vec3 position, glm::vec4 color, float distance)
{
    return std::make_shared<PointLight>(color, distance);
}
shared_ptr<AmbientLight> GameObjectFactory::createAmbientLight(
        glm::vec3 position, glm::vec4 color)
{
    return std::make_shared<AmbientLight>(color);
}