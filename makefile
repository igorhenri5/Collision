all: build_animation build_quadtree build_threadpool build_util build_graphics build_entities build_main link
.PHONY: all

link:
	g++ -o main *.o -L"glew\lib" -L"freeglut\lib" -pthread -lglew32 -lfreeglut -lopengl32

build_main:
	g++ -c main.cpp -I"freeglut\include" -I"glew\include"

build_animation:
	g++ -c animation/*.cpp -I"glew\include"

build_entities:
	g++ -c entities/*.cpp -I"glew\include"

build_util:
	g++ -c util/*.cpp -I"glew\include"

build_quadtree:
	g++ -c quadtree/*.cpp -I"glew\include"

build_threadpool:
	g++ -c threadpool/*.cpp -I"glew\include"

build_graphics:
	g++ -c graphics/*.cpp -I"glew\include"

clean:
	rm -f *.o *.exe
