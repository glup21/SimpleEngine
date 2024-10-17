#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include "json.hpp"
#include <vector>

using std::string, std::vector;
using json = nlohmann::json;

class ConfigReader
{
    string configPath;
    string scene;
    vector<string> defaultShaders;
    json config;

public:
    ConfigReader(const string& configPath);

    string getScenePath();    
};

#endif 