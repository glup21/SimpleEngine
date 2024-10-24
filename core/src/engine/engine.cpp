// Provides render pipeline

#include "engine.hpp"
#include <iostream>
#include "shaderFactory.hpp"
#include "sceneReader.hpp"
#include <thread>

bool isWindowFocused = true;
vector<bool> keys(100, false);

void window_focus_callback(GLFWwindow* window, int focused) 
{
    isWindowFocused = (focused == GLFW_TRUE);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;  
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false; 
    }
}

Engine::Engine(GLFWwindow* window, ConfigReader* configReader) : drawObjectBuffer(), configReader(configReader){
    std::cout << "Engine constructor called. drawObjectBuffer initialized to nullptr." << std::endl;
    previousTime = std::chrono::high_resolution_clock::now();

    this->window = window;
    camera = new Camera(window, configReader->getCameraSettings());

    vertexPath = configReader->getVertexShaderPath();
    fragmentPath = configReader->getFragmentShaderPath();
    
    defaultShaderProgram = new ShaderProgram(camera);
    Shader* vertexShader = ShaderFactory::createShader(GL_VERTEX_SHADER, vertexPath, camera);
    Shader* fragmentShader = ShaderFactory::createShader(GL_FRAGMENT_SHADER, fragmentPath, camera);

    defaultShaderProgram->attachShader(vertexShader);
    defaultShaderProgram->attachShader(fragmentShader);

    vertexShader->attachShaderProgram(defaultShaderProgram);
}

void Engine::init(string scenePath)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwGetWindowSize(window, &width, &height);
    
    SceneReader sceneReader(scenePath);
    Scene scene = sceneReader.readScene(defaultShaderProgram);

    // Load and init shaders
    std::cout << "Initializing engine with scene." << std::endl;
    std::cout << "Engine object address: " << this << std::endl;

    drawObjectBuffer = scene.getDrawableObjects();
    gameObjects = *scene.getObjects();

    std::cout << "drawObjectBuffer address: " << &drawObjectBuffer << std::endl;
    std::cout << "drawObjectBuffer size: " << drawObjectBuffer.size() << std::endl;

    inputManager = new Input(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);

    lastMousePosition = inputManager->getMousePos();
    defaultShaderProgram->link(); // We will link individual shader programs in models if we want
}

void Engine::run()
{
    const double targetFPS = 60.0; 
    const double targetFrameTime = 1.0 / targetFPS; 

    while (!glfwWindowShouldClose(window))
    {
        auto frameStartTime = std::chrono::high_resolution_clock::now();  
        double deltaTime = calculateDeltaTime();

        glfwGetWindowSize(window, &width, &height);
        vec2 mouseDelta(width / 2.0 - xpos, height / 2.0 - ypos);

        // Mouse movement
        if (isWindowFocused)
        {
            glfwGetCursorPos(window, &xpos, &ypos);
            vec2 mouseDelta(width / 2.0 - xpos, height / 2.0 - ypos);

            if (glm::length(mouseDelta) > 0.01f)
            {
                mouseDelta = glm::normalize(mouseDelta);
                camera->changeTarget(-mouseDelta.x, mouseDelta.y, deltaTime);
            }
        }
        glfwSetCursorPos(window, width / 2.0, height / 2.0);

        // Camera movement
        camera->move(keys, deltaTime);
        camera->notifySubscribers();

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update and draw game objects
        updateGameObjects(deltaTime);
        drawObjects();

        glfwSwapBuffers(window);
        glfwPollEvents();

        //FPS limitation
        auto frameEndTime = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> frameDuration = frameEndTime - frameStartTime;

        if (frameDuration.count() < targetFrameTime)
        {
            // Sleep for the remaining time to maintain the frame rate
            double sleepTime = targetFrameTime - frameDuration.count();
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
        }
    }
}

void Engine::shutdown()
{

}

void Engine::updateGameObjects(float delta)
{
    for (shared_ptr<IGameObject> gObj : gameObjects)
        gObj->update(delta);
}

void Engine::drawObjects()
{
    for (IDrawableObject* dObj : drawObjectBuffer)
    {
        dObj->draw();
    }
}

double Engine::calculateDeltaTime()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    return deltaTime.count();
}
