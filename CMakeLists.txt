cmake_minimum_required(VERSION 3.10)
project(SimpleEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find dependencies
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Find Assimp package
find_package(assimp REQUIRED)

# Find GLU library
find_library(GLU_LIBRARY NAMES GLU REQUIRED)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Include directories
include_directories(${ASSIMP_INCLUDE_DIRS})

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

# Add executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES} glfw GL GLEW ${GLU_LIBRARY})

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE core/headers)

# Debug target
set(CMAKE_BUILD_TYPE Debug)
