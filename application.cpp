#include "application.h"

Application::Application()
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

    window = glfwCreateWindow(800, 600, "SimpleEngine", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

        // start GLEW extension handler
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

    engine = new Engine();

}

void Application::run()
{
    //MANUAL SCENE CREATION, REPLACE LATER
    vector<float> trianglePoints = {
        0.0f, 0.75f, 0.0f,  
        0.75f, -0.25f, 0.0f, 
        -0.75f, -0.25f, 0.0f 
    };

    vector<float> squarePoints = {
        -0.25f, 0.25f, 0.0f,  
        0.25f, 0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,

        0.25f, -0.25f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.25f, 0.25f, 0.0f
    };

    Mesh triangleMesh(trianglePoints);
    Mesh squareMesh(squarePoints);

    ShaderProgram triangleShaderProgram;

    Shader* vertex = new Shader("./shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader* fragment_1 = new Shader("./shaders/fragment_2.glsl", GL_FRAGMENT_SHADER);
    Shader* fragment_2 = new Shader("./shaders/fragment_1.glsl", GL_FRAGMENT_SHADER);

    vector<Shader*> shaders = {vertex, fragment_1, fragment_2};    

    for(Shader* shader : shaders)
    {
        if(!shader->compileShader())
        {
            critical_shutdown();
        }
    }
    
    triangleShaderProgram.attachShader(*shaders.at(0));
    triangleShaderProgram.attachShader(*shaders.at(1));
    triangleShaderProgram.linkProgram();

    ShaderProgram squareShaderProgram;
    squareShaderProgram.attachShader(*shaders.at(0));
    squareShaderProgram.attachShader(*shaders.at(2));
    squareShaderProgram.linkProgram();

    Model triangleModel(&triangleMesh, &triangleShaderProgram);
    Model squareModel(&squareMesh, &squareShaderProgram);

    vector<IGameObject*> objects;
    objects.push_back(&triangleModel);
    objects.push_back(&squareModel);

    Scene scene(objects, "shaders/");

    engine->init(scene);

    while (!glfwWindowShouldClose(window))
    {
        engine->run();
    // put the stuff we’ve been drawing onto the display
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