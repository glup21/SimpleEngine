// Open window and initalizes Engine

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "mesh.h"
#include "application.h"
#include "scene.h"

int main()
{
    Application* application = new Application;

    application->initialize();
    application->run();
    application->shutdown();



    return 0;
}

/*
    GLFWwindow* window;
    GLFWerrorfun error_callback;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) 
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();


    // get version info
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    //vertex buffer object (VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW);

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


    //Square model initialization (god I hate to cramp everything inside of main)
    GLuint square_VBO = 0;
    glGenBuffers(1, &square_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, square_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_points), square_points, GL_STATIC_DRAW);

    GLuint square_VAO = 0;
    glGenVertexArrays(1, &square_VAO);
    glBindVertexArray(square_VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, square_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


     //create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);  

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    //Control of shader compilation
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }


    while (!glfwWindowShouldClose(window)){
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // draw triangles
        glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count

        glBindVertexArray(square_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
*/