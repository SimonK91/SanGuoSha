CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL

all: main.o
		$(CCC) main.o $(SDLFLAGS) -o Game.exe
	
main.o: main.cpp
		$(CCC) $(CFLAGS) -c main.cpp $(SDLFLAGS)
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf Game.exe *~
		