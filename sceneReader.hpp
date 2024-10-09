#ifndef SCENE_READER_H
#define SCENE_READER_H

#include <string>
#include "json.hpp"
#include "scene.hpp"

using std::string;
using json = nlohmann::json;

class SceneReader
{

    string scenePath;
    json sceneConfig;

public:
    SceneReader(const std::string& path) : scenePath(path) {}
    Scene readScene();

};


#endif