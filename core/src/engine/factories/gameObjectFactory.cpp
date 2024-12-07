#include "gameObjectFactory.hpp"
#include "MaterialFactory.hpp"
GameObjectFactory::GameObjectFactory()
    : modelFactory(std::make_unique<ModelFactory>())
{

}

shared_ptr<Model> GameObjectFactory::createModel(string path, int ID, string material)
{
    if(material == "default")
        return modelFactory->createModel(path, ID, SHADER_DEFAULT);
    else if(material == "ambient")
        return modelFactory->createModel(path, ID, SHADER_AMBIENT);
    else if(material == "color")
        return modelFactory->createModel(path, ID, SHADER_COLOR);

    return modelFactory->createModel(path, ID, SHADER_DEFAULT);
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