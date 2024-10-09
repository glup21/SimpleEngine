// Open window and initalizes Engine

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "mesh.hpp"
#include "application.hpp"
#include "scene.hpp"
#include <string>
#include "configReader.hpp"

int main(int argc, char* argv[])
{
    string configPath;
    if(argc > 1)
    {
       configPath =  argv[1];
    }
    else
        configPath = "config/config.json";

    ConfigReader configReader(configPath);
    string scenePath = configReader.getScenePath();

    if(scenePath.empty())
        return 1;

    Application* application = new Application(scenePath);

    application->initialize();
    application->run();
    application->shutdown();



    return 0;
}
