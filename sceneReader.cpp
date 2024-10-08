#include "sceneReader.h"
#include <fstream>
#include <iostream>
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

    std::ifstream file(scenePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open scene config: " << scenePath << std::endl;
    }
    file >> sceneConfig;




}