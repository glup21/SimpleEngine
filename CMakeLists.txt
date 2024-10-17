cmake_minimum_required(VERSION 3.10)
project(SimpleEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Find Assimp package
find_package(assimp REQUIRED)

# Include directories
include_directories(${ASSIMP_INCLUDE_DIRS})

# Source files
set(SRCS
    main.cpp
    application.cpp
    texture.cpp
    engine.cpp
    scene.cpp
    mesh.cpp
    shader.cpp
    model.cpp
    sceneReader.cpp
    configReader.cpp
    imageLoader.cpp
    shaderProgram.cpp
    transform.cpp
    camera.cpp
    input.cpp
    
)

# Add executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES} glfw GL GLEW)

# Debug target
set(CMAKE_BUILD_TYPE Debug)