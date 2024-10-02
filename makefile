PATHS = main.cpp application.cpp engine.cpp scene.cpp mesh.cpp shader.cpp

all:
	g++ $(PATHS) -lglfw -lGL -lGLEW -o main