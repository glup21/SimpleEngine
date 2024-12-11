cmake_minimum_required(VERSION 3.10)
project(SimpleEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug target
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Find required packages
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)

# Find GLU library
find_library(GLU_LIBRARY GLU REQUIRED)

# Include directories
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(core/headers)

# Source files
set(SRCS
    # Main
    core/src/main.cpp
    core/src/application.cpp

    # Engine
    core/src/engine/texture.cpp
    core/src/engine/engine.cpp
    core/src/engine/camera.cpp
    core/src/engine/input.cpp
    core/src/engine/shader.cpp
    core/src/engine/shaderProgram.cpp
    core/src/engine/pointLight.cpp
    core/src/engine/transformComposite.cpp
    core/src/engine/AmbientLight.cpp
    core/src/engine/spotLight.cpp
    core/src/engine/Material.cpp

    # Config
    core/src/config/configReader.cpp

    # Scene
    core/src/scene/scene.cpp
    core/src/scene/mesh.cpp
    core/src/scene/model.cpp
    core/src/scene/sceneReader.cpp

    # Loaders
    core/src/engine/imageLoader.cpp
    core/src/engine/loaders/modelLoader.cpp

    # Factories
    core/src/engine/factories/gameObjectFactory.cpp
    core/src/engine/factories/modelFactory.cpp
    core/src/engine/factories/MaterialFactory.cpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    glfw
    GLEW
    ${GLU_LIBRARY}
    ${ASSIMP_LIBRARIES}
    GL # For OpenGL
)

# Include directories for the target
target_include_directories(${PROJECT_NAME} PRIVATE core/headers)

# Output messages
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Assimp include dirs: ${ASSIMP_INCLUDE_DIRS}")
message(STATUS "GLU library: ${GLU_LIBRARY}")
