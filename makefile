all: build_quadtree build_threadpool build_util build_entities build_main link
.PHONY: all

link:
	g++ -o main *.o -pthread 

build_main:
	g++ -c main.cpp 

build_entities:
	g++ -c entities/*.cpp 

build_util:
	g++ -c util/*.cpp 

build_quadtree:
	g++ -c quadtree/*.cpp 

build_threadpool:
	g++ -c threadpool/*.cpp 

clean:
	rm -f *.o *.exe
