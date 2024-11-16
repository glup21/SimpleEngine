#include "application.hpp"
#include <iostream>
#include "stb_image.h"
#include "sceneReader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

Application::Application(ConfigReader* configReader): configReader(configReader)
{
    
}

void Application::initialize() 
{
    //Create window
    
    GLFWerrorfun error_callback;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) 
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE); 
    }
    scenePath = configReader->getScenePath(0);
    window = glfwCreateWindow(1024, 768, "SimpleEngine", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not initialize GLEW\n");
        return;
    }

    // get version info
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    engine = new Engine(window, configReader);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

}

void Application::run()
{

    engine->init(scenePath);
    while (!glfwWindowShouldClose(window))
    {

        engine->run();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }



}

void Application::shutdown()
{
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void Application::critical_shutdown()
{
    printf("CRITICALL ERROR, SHUTDOWN\n");
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}