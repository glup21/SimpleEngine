#include "configReader.hpp"
#include <fstream>
#include <iostream>
#include <filesystem> 
#include <string>

namespace fs = std::filesystem; 

ConfigReader::ConfigReader(const string& configPath): configPath(configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << configPath << std::endl;
        return; 
    }

    file >> config;

    if (config.contains("scenes")) {
        scenesPath = config["scenes"].get<string>(); 
        std::cout << "Scenes path: " << scenesPath << std::endl;

        for (auto file : fs::directory_iterator(scenesPath)) {
            if (file.is_regular_file() && file.path().extension() == ".json") 
            { 
                scenes.push_back(file.path().string()); 
            }
        }
    } 
    else {
        std::cerr << "Error: scenes property is not defined " << std::endl;
    }

    if (config.contains("camera")) {
        json cameraConfig = config["camera"];

        cameraSettings.fov = cameraConfig["fov"].get<float>();
        cameraSettings.nearPlane = cameraConfig["nearPlane"].get<float>();
        cameraSettings.farPlane = cameraConfig["farPlane"].get<float>();
        cameraSettings.lookSensitivity = cameraConfig["lookSensitivity"].get<float>();
        cameraSettings.movingSpeed = cameraConfig["movingSpeed"].get<float>();
    } else {
        std::cerr << "Error: camera settings are not defined " << std::endl;
    }

    if (config.contains("vertex_shader")) {
        vertexShaderPath = config["vertex_shader"].get<string>();
    }

    if (config.contains("fragment_shader")) {
        fragmentShaderPath = config["fragment_shader"].get<string>();
    }
}

string ConfigReader::getScenePath(int ID) {
    if (ID >= 0 && ID < scenes.size()) 
        return scenes.at(ID);
    else 
        return "";
}

CameraSettings ConfigReader::getCameraSettings() {
    return cameraSettings;
}

string ConfigReader::getVertexShaderPath() {
    return vertexShaderPath;
}

string ConfigReader::getFragmentShaderPath() {
    return fragmentShaderPath;
}
