CCC        =g++
OBJECTS = ./objects
CFLAGS   +=-I$(OBJECTS) -L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf

all: main.cpp functions.o $(OBJECTS)/objects.h button.o
		$(CCC) $(CFLAGS) main.cpp functions.o button.o $(SDLFLAGS) -o "SGS.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SGS.exe
		@ echo
		
button.o: $(OBJECTS)/button.h $(OBJECTS)/button.cpp functions.h
		$(CCC) $(CFLAGS) -c $(OBJECTS)/button.cpp functions.o $(SDLFLAGS)
		
functions.o: functions.cpp functions.h
		$(CCC) $(CFLAGS) -c functions.cpp $(SDLFLAGS)
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SGS.exe" *~
		