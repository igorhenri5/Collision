all: build_animation build_entities build_quadtree build_threadpool build_util build_graphics build_main link
.PHONY: all

link:
	g++ -o main *.o -L"C:\MinGW\glew\lib" -L"C:\MinGW\freeglut\lib" -pthread -lglew32 -lfreeglut -lopengl32 -Wl,--subsystem,windows

build_main:
	g++ -c main.cpp -I"C:\MinGW\freeglut\include"

build_animation:
	g++ -c animation/*.cpp

build_entities:
	g++ -c entities/*.cpp

build_util:
	g++ -c util/*.cpp

build_quadtree:
	g++ -c quadtree/*.cpp

build_threadpool:
	g++ -c threadpool/*.cpp

build_graphics:
	g++ -c graphics/DrawableBuffer.cpp -I"C:\MinGW\glew\include"

clean:
	rm -f *.o *.exe
