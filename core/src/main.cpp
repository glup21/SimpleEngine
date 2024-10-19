#include <GL/glew.h>
#include <GLFW/glfw3.h>
 
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
       configPath = argv[1];
    }
    else
        configPath = "../core/config/config.json";

    ConfigReader configReader(configPath);
    string scenePath = configReader.getScenePath();

    if(scenePath.empty())
        return 1;

    Application* application = new Application(&configReader);

    application->initialize();
    application->run();
    application->shutdown();



    return 0;
}
