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

    

}

string ConfigReader::getScenePath()
{
    return scene;
}

