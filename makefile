PATHS = main.cpp application.cpp texture.cpp engine.cpp scene.cpp mesh.cpp baseImage.cpp shader.cpp model.cpp shaderProgram.cpp sceneReader.cpp configReader.cpp material.cpp
FLAGS = -lglfw -lGL -lGLEW 

all:
	g++ $(PATHS) $(FLAGS) -o main

debug:
	g++ -g $(PATHS) $(FLAGS) -o main && gdb ./main