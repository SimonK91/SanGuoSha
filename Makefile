CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL 
#-lSDL_image -lSDL_ttf

all: main.o
		@ $(CCC) main.o $(SDLFLAGS) -o "San Guo Sha.exe"
	
main.o: main.cpp
		@ $(CCC) $(CFLAGS) -c main.cpp $(SDLFLAGS)
		
#button.o: Button.cc Button.h
#		$(CCC) $(CFLAGS) -c Button.cc $(SDLFLAGS)
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "San Guo Sha.exe" *~
		