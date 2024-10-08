#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include "json.hpp"

using std::string;
using json = nlohmann::json;

class ConfigReader
{
    string configPath;
    string scene;
    json config;

public:
    ConfigReader(const string& configPath);

    string getScenePath();    
};

#endif 