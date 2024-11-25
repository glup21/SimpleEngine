#include "application.hpp"
#include <iostream>
#include "stb_image.h"
#include "sceneReader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Application::Application(ConfigReader* configReader)
    : configReader(configReader), engine(nullptr), input(nullptr)
{
}

void Application::initialize()
{
    // Create window
    glfwSetErrorCallback([](int error, const char* description) {
        fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
    });

    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    scenePath = configReader->getScenePath(0);
    window = glfwCreateWindow(1024, 768, "SimpleEngine", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "ERROR: could not initialize GLEW\n");
        return;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    loadScene(0);
    std::cout << "After load scene\n" << std::endl;
}

void Application::run()
{
    while (!glfwWindowShouldClose(window))
    {
        std::cout << "Checkpoint: Before engine->run()" << std::endl;
        if (engine) engine->run();
        std::cout << "Checkpoint: After engine->run()" << std::endl;


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::shutdown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::critical_shutdown()
{
    printf("CRITICAL ERROR, SHUTDOWN\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}

void Application::loadScene(int sceneID)
{
    if (engine.get() != nullptr)
    {
        //engine->shutdown();
        engine.reset();
    }

    engine = std::make_unique<Engine>(window, configReader);
    engine->init(configReader->getScenePath(sceneID));

    if (input == nullptr || input->getEngine() != engine.get())
        input = std::make_shared<Input>(window, this, engine.get());

    input->setEngine(engine.get());
    engine->addInput(input);
}
