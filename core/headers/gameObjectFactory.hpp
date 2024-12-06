#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

#include "IObjectFactory.hpp"
#include "modelFactory.hpp"
#include <memory>
#include "shaderProgram.hpp"
#include "model.hpp"
#include "pointLight.hpp"
#include "AmbientLight.hpp"
#include "SpotLight.hpp"

using std::unique_ptr, std::shared_ptr;

class GameObjectFactory : public IObjectFactory
{
private:
    unique_ptr<ModelFactory> modelFactory;
    ShaderProgram* defaultShaderProgram;

public:
    GameObjectFactory(ShaderProgram* defaultShaderProgram);
    ~GameObjectFactory() = default;

    shared_ptr<Model> createModel(string path, int ID); //other ways of creation implement later
    shared_ptr<PointLight> createPointLight(
        glm::vec3 position = glm::vec3(0.0), glm::vec4 color = glm::vec4(1.0), float distance = 1.0);
    shared_ptr<SpotLight> createSpotLight(
        glm::vec3 position = glm::vec3(0.0), glm::vec4 color = glm::vec4(1.0), float distance = 1.0, float angle = 45);
    shared_ptr<AmbientLight> createAmbientLight(
        glm::vec3 position = glm::vec3(0.0), glm::vec4 color = glm::vec4(1.0)
    );
};

#endif