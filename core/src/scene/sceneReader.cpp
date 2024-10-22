#include "sceneReader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include "transform.hpp"
#include "gameObjectFactory.hpp"
#include "pointLight.hpp"

Scene SceneReader::readScene(ShaderProgram* defaultShaderProgram)
{
    //ModelFactory modelFactory(defaultShaderProgram);
    GameObjectFactory objectFactory(defaultShaderProgram);

    std::ifstream file(scenePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open scene config: " << scenePath << std::endl;
    }
    file >> sceneConfig;

    
    vector<shared_ptr<IGameObject>> gObj;

    if(sceneConfig.contains("objects"))
    {
        for(auto& obj : sceneConfig["objects"])
        {
            string type = obj.value("type", "");
            if (type == "model")
            {
                string id = obj.value("id", "");
                string directory = obj.value("directory", "");
                vector<float> position = obj.value("position", vector<float>{});
                vector<float> rotation = obj.value("rotation", vector<float>{});
                vector<float> scale = obj.value("scale", vector<float>{});

                glm::vec3 v_position{position[0], position[1], position[2]};
                glm::vec3 v_rotation{rotation[0], rotation[1], rotation[2]};
                glm::vec3 v_scale{scale[0], scale[1], scale[2]};

                std::shared_ptr<Model> model = objectFactory.createModel(directory, id);

                model->addScale(v_scale);
                model->addRotation({1.0f, 0.0f, 0.0f}, v_rotation.x);
                model->addRotation({0.0f, 1.0f, 0.0f}, v_rotation.y);
                model->addRotation({0.0f, 0.0f, 1.0f}, v_rotation.z);
                model->addPosition(v_position);

                gObj.push_back(model);
            }
            else if(type == "point_light")
            {
                vector<float> position = obj.value("position", vector<float>{});
                glm::vec3 v_position{position[0], position[1], position[2]};
                shared_ptr<PointLight> light = objectFactory.createLight();

                light->addPosition(v_position);
                gObj.push_back(light);
            }
    }


    }
    Scene scene(gObj);
    return scene;
}