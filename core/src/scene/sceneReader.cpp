#include "sceneReader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include "transform.hpp"

Scene SceneReader::readScene(ShaderProgram* defaultShaderProgram)
{

    std::ifstream file(scenePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open scene config: " << scenePath << std::endl;
    }
    file >> sceneConfig;

    
    vector<IGameObject*> gObj;

    if(sceneConfig.contains("objects"))
    {
        for(auto& obj : sceneConfig["objects"])
        {
            string id = obj.value("id", "");
            string type = obj.value("type", "");
            string directory = obj.value("directory", "");
            vector<float> position = obj.value("position", vector<float>{});
            vector<float> rotation = obj.value("rotation", vector<float>{});
            vector<float> scale = obj.value("scale", vector<float>{});

            if(type == "model")
            {
                
                glm::vec3 v_position{position[0], position[1], position[2]};
                glm::vec3 v_rotation{rotation[0], rotation[1], rotation[2]};
                glm::vec3 v_scale{scale[0], scale[1], scale[2]};
                Transform transform;
                
                // transform.scale(v_scale.x, v_scale.y, v_scale.z); 
                
                // transform.rotate(v_rotation.x, 1.0f, 0.0f, 0.0f); 
                // transform.rotate(v_rotation.y, 0.0f, 1.0f, 0.0f); 
                // transform.rotate(v_rotation.z, 0.0f, 0.0f, 1.0f);
                // transform.translate(v_position.x, v_position.y, v_position.z); 

                Model* model = new Model(directory, id, defaultShaderProgram); 

                model->addScale(v_scale);
                model->addRotation({1.0f, 0.0f, 0.0f}, v_rotation.x);
                model->addRotation({0.0f, 1.0f, 0.0f}, v_rotation.y);
                model->addRotation({0.0f, 0.0f, 1.0f}, v_rotation.z);

                model->addPosition(v_position);


                gObj.push_back(model);

            }
        }


    }
    Scene scene(gObj);
    return scene;
}