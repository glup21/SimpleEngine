#include "sceneReader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include "gameObjectFactory.hpp"
#include "pointLight.hpp"
#include "SpotLight.hpp"

Scene SceneReader::readScene(ShaderProgram* defaultShaderProgram)
{
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

                std::shared_ptr<Model> model = objectFactory.createModel(directory, 0);

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

                vector<float> color = obj.value("color", vector<float>{1.0, 1.0, 1.0});
                float brightness = obj.value("brightness", 1.0f);
                glm::vec4 v_color{color[0], color[1], color[2], brightness};

                float distance = obj.value("distance", 1.0f);
        
                shared_ptr<PointLight> light = objectFactory.createPointLight(
                    v_position, v_color, distance);
                std::cout << light << std::endl;

                defaultShaderProgram->observe(light.get());
                light->addPosition(v_position);            
                gObj.push_back(light);
                
                
            }
            else if(type == "ambient_light")
            {
                vector<float> position = obj.value("position", vector<float>{});
                glm::vec3 v_position{position[0], position[1], position[2]};

                vector<float> color = obj.value("color", vector<float>{1.0, 1.0, 1.0});
                float brightness = obj.value("brightness", 1.0f);
                glm::vec4 v_color{color[0], color[1], color[2], brightness};

                shared_ptr<AmbientLight> light = objectFactory.createAmbientLight(
                    v_position, v_color
                );
                defaultShaderProgram->observe(light.get());
                light->addPosition(v_position);
                gObj.push_back(light);
                

                
            }
            else if(type == "spot_light")
            {
                vector<float> position = obj.value("position", vector<float>{});
                glm::vec3 v_position{position[0], position[1], position[2]};

                vector<float> rotation = obj.value("rotation", vector<float>{});
                glm::vec3 v_rotation{rotation[0], rotation[1], rotation[2]};

                vector<float> color = obj.value("color", vector<float>{1.0, 1.0, 1.0});
                float brightness = obj.value("brightness", 1.0f);
                glm::vec4 v_color{color[0], color[1], color[2], brightness};

                float v_angle = obj.value("angle", 45.0f);

                shared_ptr<SpotLight> light = objectFactory.createSpotLight(
                    v_position, v_color, v_angle
                );
                defaultShaderProgram->observe(light.get());
                light->addPosition(v_position);
                light->addRotation({1.0f, 0.0f, 0.0f}, v_rotation.x);
                light->addRotation({0.0f, 1.0f, 0.0f}, v_rotation.y);
                light->addRotation({0.0f, 0.0f, 1.0f}, v_rotation.z);
                gObj.push_back(light);
                

                
            }
    }


    }
    Scene scene(gObj);
    return scene;
}