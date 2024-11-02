#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include "json.hpp"
#include <vector>
#include "cameraSettings.hpp"

using std::string, std::vector;
using json = nlohmann::json;

class ConfigReader
{
    string configPath;
    string scenesPath;
    vector<string> scenes;
    json config;
    CameraSettings cameraSettings;
    string vertexShaderPath;
    string fragmentShaderPath;

public:
    ConfigReader(const string& configPath);

    string getScenePath(int ID);  
    CameraSettings getCameraSettings();
    string getVertexShaderPath();
    string getFragmentShaderPath();
};

#endif 