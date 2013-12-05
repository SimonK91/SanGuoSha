CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS +=-lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
OBJECTS = main.cpp  gameCard.o heroCard.o card.o menu.o game.o Button.o Slider.o Textbox.o Checkbox.o Functions.o Window.o music.o SGS.o cardList.o FrameRateFixer.o Timer.o PopupText.o Player.o

all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS) -o "SanGuoSha.exe"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SanGuoSha.exe
		@ echo

		
FrameRateFixer.o: FrameRateFixer.cpp FrameRateFixer.h
		@ echo FrameRateFixer.o skapas
		@$(CCC) $(CFLAGS) -c FrameRateFixer.cpp $(SDLFLAGS)
		
Functions.o: functions.cpp functions.h
		@ echo functions.o skapas
		@$(CCC) $(CFLAGS) -c functions.cpp $(SDLFLAGS)
		
music.o: music.h music.cpp
		@ echo music.o skapas
		@$(CCC) $(CFLAGS) -c music.cpp $(SDLFLAGS)
		
menu.o: menu.cpp menu_commands.cpp
		@ echo Menu.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c menu.cpp $(SDLFLAGS)
		
game.o: game.cpp game_commands.cpp card_commands.cpp
		@ echo Game.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c game.cpp $(SDLFLAGS)
		
SGS.o: SGS.cpp SGS.h	
		@ echo SGS.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c SGS.cpp $(SDLFLAGS)
		
Player.o: Player.cpp Player.h	
		@ echo Player.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c Player.cpp $(SDLFLAGS)
		
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
			
gameCard.o: ./objects/gameCard.h ./objects/gameCard.cpp
		@ echo gameCard.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/gameCard.cpp $(SDLFLAGS)
		
heroCard.o: ./objects/heroCard.h ./objects/heroCard.cpp
		@ echo heroCard.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/heroCard.cpp $(SDLFLAGS)

cardList.o: ./objects/cardList.h ./objects/cardList.cpp
		@ echo cardList.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/cardList.cpp $(SDLFLAGS)

card.o: ./objects/card.h ./objects/card.cpp
		@ echo card.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/card.cpp $(SDLFLAGS)
	
PopupText.o: ./objects/PopupText.h ./objects/PopupText.cpp
		@ echo PopupText.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/PopupText.cpp $(SDLFLAGS)
	
Timer.o: Timer.h Timer.cpp
	@ echo Timer.o skapas
	@$(CCC) $(CFLAGS) -c Timer.cpp $(SDLFLAGS)
		
		
clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SanGuoSha.exe" *~ stderr.txt stdout.txt
		