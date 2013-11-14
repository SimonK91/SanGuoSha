CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJECTS = main.cpp Menu.o Button.o Slider.o Textbox.o Checkbox.o Functions.o Window.o music.o SGS.o
all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SanGuoSha.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SanGuoSha.exe
		@ echo

		
		
Functions.o: Functions.cpp Functions.h
		@ echo Functions.o skapas
		@$(CCC) $(CFLAGS) -c Functions.cpp $(SDLFLAGS)
		
music.o: music.h music.cpp
		@ echo music.o skapas
		@$(CCC) $(CFLAGS) -c music.cpp $(SDLFLAGS)
		
Menu.o: menu.cpp menu_commands.cpp
		@ echo Menu.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c menu.cpp $(SDLFLAGS)
		
Game.o: game.cpp game_commands.cpp
		@ echo Game.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c game.cpp $(SDLFLAGS)
		
SGS.o: SGS.cpp SGS.h	
		@ echo SGS.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c SGS.cpp $(SDLFLAGS)
		
Button.o: ./objects/Button.h ./objects/Button.cpp
		@ echo Button.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Button.cpp $(SDLFLAGS)
		
Checkbox.o: ./objects/Checkbox.h ./objects/Checkbox.cpp
		@ echo Checkbox.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Checkbox.cpp $(SDLFLAGS)
		
Slider.o: ./objects/Slider.h ./objects/Slider.cpp
		@ echo Slider.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Slider.cpp $(SDLFLAGS)
		
Window.o: ./objects/Window.h ./objects/Window.cpp
		@ echo Window.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Window.cpp $(SDLFLAGS)
		
Textbox.o: ./objects/Textbox.h ./objects/Textbox.cpp
		@ echo Textbox.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Textbox.cpp $(SDLFLAGS)
			
clean:
		 del *.o

zap: clean
		del *.exe
		