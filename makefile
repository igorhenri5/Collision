build:
	g++ -c -o main.o main.cpp -I"C:\MinGW\freeglut\include"
	g++ -o main main.o -L"C:\MinGW\freeglut\lib" -lfreeglut -lopengl32 -Wl,--subsystem,windows

build_cygwin:
	g++ -o main main.cpp -lopengl32 -lglut

clean:
	rm -f *.o *.exe
