all: build_util build_quadtree build_main link
.PHONY: all

link:
	g++ -o main main.o -L"C:\MinGW\freeglut\lib" -lfreeglut -lopengl32 -Wl,--subsystem,windows

build_main:
	g++ -c -o main.o main.cpp -I"C:\MinGW\freeglut\include"

build_util:
	g++ -c -o Rect.o util/Rect.cpp

build_quadtree:
	g++ -c -o QuadTree.o quadtree/QuadTree.cpp

build_framework:
	g++ -c -o ShaderProvider.o framework/ShaderProvider.cpp
	g++ -c -o DrawableBuffer.o framework/DrawableBuffer.cpp

clean:
	rm -f *.o *.exe
