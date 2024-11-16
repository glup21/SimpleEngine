#ifndef SCENE_READER_H
#define SCENE_READER_H

#include <string>
#include "json.hpp"
#include "scene.hpp"
#include "IGameObject.hpp"
#include "model.hpp"
#include "shaderProgram.hpp"
#include "modelFactory.hpp"
using std::string;
using json = nlohmann::json;

class SceneReader
{

    string scenePath;
    json sceneConfig;

public:
    SceneReader(const string& path) : scenePath(path) {}
    Scene readScene(ShaderProgram* defaultShaderProgram);

};


#endif