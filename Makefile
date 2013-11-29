CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_net
OBJECTS = main.cpp Menu.o Button.o Slider.o Textbox.o Checkbox.o Functions.o Window.o music.o SGS.o Network.o Timer.o StringInput.o SgsServer.o Settings.o Clickbox.o
all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SanGuoSha.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SanGuoSha.exe
		@ echo

server: server/server.cpp
		@ echo
		@ echo server skapas
		@$(CCC) $(CFLAGS) server/server.cpp $(SDLFLAGS) -o "server.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar server.exe
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
	
Clickbox.o: ./objects/ClickBox.cpp ./objects/ClickBox.h
		@ echo Clickbox.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/ClickBox.cpp $(SDLFLAGS)
		
Slider.o: ./objects/Slider.h ./objects/Slider.cpp
		@ echo Slider.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Slider.cpp $(SDLFLAGS)
		
Window.o: ./objects/Window.h ./objects/Window.cpp
		@ echo Window.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Window.cpp $(SDLFLAGS)
		
Textbox.o: ./objects/Textbox.h ./objects/Textbox.cpp
		@ echo Textbox.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Textbox.cpp $(SDLFLAGS)
		
Network.o: Network.h Network.cpp
		@ echo Network.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c Network.cpp $(SDLFLAGS)

Timer.o: Timer.h Timer.cpp
		@ echo Timer.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c Timer.cpp $(SDLFLAGS)	

StringInput.o: StringInput.h StringInput.cpp
			@ echo Input.o skapas
			@$(CCC) $(INCLUDE) $(CFLAGS) -c StringInput.cpp $(SDLFLAGS)

SgsServer.o: sgsServer.h sgsServer.cpp
			@ echo sgsServer.o skapas
			@$(CCC) $(INCLUDE) $(CFLAGS) -c sgsServer.cpp $(SDLFLAGS)
		
Settings.o: settings.h settings.cpp
	@ echo Settings.o skapas
	@$(CCC) $(INCLUDE) $(CFLAGS) -c settings.cpp $(SDLFLAGS)
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SanGuoSha.exe" *~
