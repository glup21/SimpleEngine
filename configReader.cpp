#include "configReader.hpp"
#include <fstream>
#include <iostream>

ConfigReader::ConfigReader(const string& configPath): configPath(configPath)
{

    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << configPath << std::endl;
    }
    file >> config;

    if (config.contains("scene")) {
        std::cout << scene << std::endl;
        scene =  config["scene"].get<string>();
        
    } 
    else
    {
        std::cerr << "Error: scene property is not defined " << std::endl;
    }

    if(config.contains("camera"))
    {
        json cameraConfig = config["camera"];

        cameraSettings.fov = cameraConfig["fov"].get<float>();
        cameraSettings.nearPlane = cameraConfig["nearPlane"].get<float>();
        cameraSettings.farPlane = cameraConfig["farPlane"].get<float>();
        cameraSettings.lookSensitivity = cameraConfig["lookSensitivity"].get<float>();
        cameraSettings.movingSpeed = cameraConfig["movingSpeed"].get<float>();
    }
    else
        std::cerr << "Error: camera settings are not defined " << std::endl;

    

}

string ConfigReader::getScenePath()
{
    return scene;
}
CameraSettings ConfigReader::getCameraSettings()
{
    return cameraSettings;
}
