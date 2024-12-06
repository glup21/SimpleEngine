#include "gameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(ShaderProgram* defaultShaderProgram)
    : defaultShaderProgram(defaultShaderProgram), modelFactory(std::make_unique<ModelFactory>(defaultShaderProgram))
{

}

shared_ptr<Model> GameObjectFactory::createModel(string path, int ID)
{
    return modelFactory->createModel(path, ID);
}

shared_ptr<PointLight> GameObjectFactory::createPointLight(
        glm::vec3 position, glm::vec4 color, float distance)
{
    return std::make_shared<PointLight>(color, distance);
}

shared_ptr<SpotLight> GameObjectFactory::createSpotLight(
        glm::vec3 position, glm::vec4 color, float distance, float angle)
{
    return std::make_shared<SpotLight>(color, distance, angle);
}

shared_ptr<AmbientLight> GameObjectFactory::createAmbientLight(
        glm::vec3 position, glm::vec4 color)
{
    return std::make_shared<AmbientLight>(color);
}