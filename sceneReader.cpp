#include "sceneReader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include "transform.hpp"
    // //MANUAL SCENE CREATION, REPLACE LATER
    // vector<float> trianglePoints = {
    //     0.0f, 0.75f, 0.0f,  
    //     0.75f, -0.25f, 0.0f, 
    //     -0.75f, -0.25f, 0.0f 
    // };

    // float triangleTexCoords[] = 
    // {
    //     0.0f, 0.0f,
    //     1.0f, 0.0f,
    //     0.5f, 1.0f
    // };
    // unsigned int texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // // set the texture wrapping/filtering options (on the currently bound texture object)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // int width, height, nrChannels;
    // //Load texture by bytes
    // unsigned char *data = stbi_load("textures/wall.jpg", &width, &height, &nrChannels, 0);
    // //Create texture object

    // glGenTextures(1, &texture); 
    // glBindTexture(GL_TEXTURE_2D, texture);  
    // //Attach to a texture object texture image
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // //Generate mipmap
    // glGenerateMipmap(GL_TEXTURE_2D);
    // stbi_image_free(data);

    // vector<float> squarePoints = {
    //     -0.25f, 0.25f, 0.0f,  
    //     0.25f, 0.25f, 0.0f,
    //     0.25f, -0.25f, 0.0f,

    //     0.25f, -0.25f, 0.0f,
    //     -0.25f, -0.25f, 0.0f,
    //     -0.25f, 0.25f, 0.0f
    // };

    // Mesh triangleMesh(trianglePoints);
    // Mesh squareMesh(squarePoints);

    // ShaderProgram triangleShaderProgram;

    // Shader* vertex = new Shader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
    // Shader* fragment_1 = new Shader("./shaders/fragment_2.glsl", GL_FRAGMENT_SHADER);
    // Shader* fragment_2 = new Shader("./shaders/fragment_1.glsl", GL_FRAGMENT_SHADER);

    // vector<Shader*> shaders = {vertex, fragment_1, fragment_2};    

    // for(Shader* shader : shaders)
    // {
    //     if(!shader->compileShader())
    //     {
    //         critical_shutdown();
    //     }
    // }
    // //std::cout << "Vertex shader:" << shaders.at(0)->getShader() << std::endl;
    // triangleShaderProgram.attachShader(*shaders.at(0));
    // triangleShaderProgram.attachShader(*shaders.at(1));
    // triangleShaderProgram.linkProgram();

    // ShaderProgram squareShaderProgram;
    // squareShaderProgram.attachShader(*shaders.at(0));
    // squareShaderProgram.attachShader(*shaders.at(2));
    // squareShaderProgram.linkProgram();

    // Model triangleModel(&triangleMesh, &triangleShaderProgram);
    // Model squareModel(&squareMesh, &squareShaderProgram);

    // vector<IGameObject*> objects;
    // objects.push_back(&triangleModel);
    // objects.push_back(&squareModel);

    // Scene scene(objects, "shaders/");
Scene SceneReader::readScene()
{
    /*
        "objects":
    [
        {
            "id": "monkey",
            "type" : "model",
            "directory" : "../models/crowbar/Crowbar.obj",
            "position" : [0, 0, 0],
            "rotation" : [0, 0, 0],
            "scale" : [1, 1, 1]
        }
    ]*/

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
                glm::quat v_rotation{1.0f, rotation[0], rotation[1], rotation[2]};
                glm::vec3 v_scale{scale[0], scale[1], scale[2]};
            
                Transform transform(v_position, v_rotation, v_scale);
                Model* model = new Model(directory, id, transform); 

                gObj.push_back(model);

            }
        }


    }
    Scene scene(gObj);
    return scene;
}