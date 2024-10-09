cmake_minimum_required(VERSION 3.10)
project(SimpleEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Manually specify the path to the Assimp headers and library
set(ASSIMP_INCLUDE_DIR assimp/include)
set(ASSIMP_LIBRARY assimp/lib/libassimp.so) # Adjust the path and library name as needed

# Include directories
include_directories(${ASSIMP_INCLUDE_DIR})

# Source files
set(SRCS
    main.cpp
    application.cpp
    texture.cpp
    engine.cpp
    scene.cpp
    mesh.cpp
    baseImage.cpp
    shader.cpp
    model.cpp
    sceneReader.cpp
    configReader.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY} glfw GL GLEW)

# Debug target
set(CMAKE_BUILD_TYPE Debug)