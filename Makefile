CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf
OBJECTS = main.cpp game_state.o object_button.o functions.o pointer_arrow.o
all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SGS.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SGS.exe
		@ echo


		
functions.o: functions.cpp functions.h
		@ echo
		@ echo functions.o skapas
		$(CCC) $(CFLAGS) -c functions.cpp $(SDLFLAGS)
		
game_state.o: game_state.cpp game_state.h
		@ echo
		@ echo game_state.o skapas
		$(CCC) $(INCLUDE) $(CFLAGS) -c game_state.cpp $(SDLFLAGS)
		
object_button.o: ./objects/object_button.h ./objects/object_button.cpp
		@ echo
		@ echo object_button.o skapas
		$(CCC) $(CFLAGS) -c ./objects/object_button.cpp $(SDLFLAGS)
		
pointer_arrow.o: ./objects/pointer_arrow.h ./objects/pointer_arrow.cpp
		@ echo
		@ echo pointer_arrow.o skapas
		$(CCC) $(CFLAGS) -c ./objects/pointer_arrow.cpp $(SDLFLAGS)
		
		
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SGS.exe" *~
		