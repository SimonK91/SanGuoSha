CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJECTS = main.cpp game_state.o object_button.o object_slider.o object_text_box.o object_check_box.o functions.o object_window.o music.o
all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SGS.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SGS.exe
		@ echo

		
functions.o: functions.cpp functions.h
		@ echo functions.o skapas
		@$(CCC) $(CFLAGS) -c functions.cpp $(SDLFLAGS)
		
music.o: music.h music.cpp
		@ echo music.o skapas
		@$(CCC) $(CFLAGS) -c music.cpp $(SDLFLAGS)
		
game_state.o: game_state.cpp game_state_commands.cpp game_state.h
		@ echo game_state.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c game_state.cpp $(SDLFLAGS)
		
object_button.o: ./objects/object_button.h ./objects/object_button.cpp
		@ echo object_button.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/object_button.cpp $(SDLFLAGS)
		
object_check_box.o: ./objects/object_check_box.h ./objects/object_check_box.cpp
		@ echo object_check_box.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/object_check_box.cpp $(SDLFLAGS)
		
object_slider.o: ./objects/object_slider.h ./objects/object_slider.cpp
		@ echo object_slider.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/object_slider.cpp $(SDLFLAGS)
		
object_window.o: ./objects/object_window.h ./objects/object_window.cpp
		@ echo object_window.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/object_window.cpp $(SDLFLAGS)
		
object_text_box.o: ./objects/object_text_box.h ./objects/object_text_box.cpp
		@ echo object_text_box.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/object_text_box.cpp $(SDLFLAGS)
		
pointer_arrow.o: ./objects/pointer_arrow.h ./objects/pointer_arrow.cpp
		@ echo pointer_arrow.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/pointer_arrow.cpp $(SDLFLAGS)
		
		
		
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SGS.exe" *~
		