#include "sceneReader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp>
#include "transform.hpp"

Scene SceneReader::readScene()
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
                //glm::quat v_rotation{1.0f, rotation[0], rotation[1], rotation[2]};
                glm:: quat v_rotation = glm::normalize(glm::quat(glm::radians(vec3(rotation[0], rotation[1], rotation[2]))));
                glm::vec3 v_scale{scale[0], scale[1], scale[2]};
            
                Transform transform(v_position, glm::normalize(v_rotation), v_scale);
                Model* model = new Model(directory, id, transform); 

                gObj.push_back(model);

            }
        }


    }
    Scene scene(gObj);
    return scene;
}