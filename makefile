PATHS = main.cpp application.cpp engine.cpp scene.cpp mesh.cpp shader.cpp model.cpp shaderProgram.cpp

all:
	g++ $(PATHS) -lglfw -lGL -lGLEW -o main

debug:
	g++ -g $(PATHS) -lglfw -lGL -lGLEW -o main && gdb ./main