CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJECTS = main.cpp gameCard.o heroCard.o card.o Menu.o Button.o ClickBox.o Slider.o Textbox.o Checkbox.o Functions.o Window.o music.o SGS.o cardList.o
all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SanGuoSha.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SanGuoSha.exe
		@ echo

		
		
Functions.o: functions.cpp functions.h
		@ echo functions.o skapas
		@$(CCC) $(CFLAGS) -c functions.cpp $(SDLFLAGS)
		
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
		
ClickBox.o: ./objects/ClickBox.h ./objects/ClickBox.cpp
		@ echo ClickBox.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/ClickBox.cpp $(SDLFLAGS)
		
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
			
gameCard.o: ./objects/gameCard.h ./objects/gameCard.cpp
		@ echo gameCard.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c ./objects/gameCard.cpp $(SDLFLAGS)
		
heroCard.o: ./objects/heroCard.h ./objects/heroCard.cpp
		@ echo heroCard.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/heroCard.cpp $(SDLFLAGS)

cardList.o: ./objects/cardList.h ./objects/cardList.cpp
		@ echo cardList.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/cardList.cpp $(SDLFLAGS)

card.o: ./objects/card.h ./objects/card.cpp
		@ echo card.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/card.cpp $(SDLFLAGS)
		
		
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SanGuoSha.exe" *~
		