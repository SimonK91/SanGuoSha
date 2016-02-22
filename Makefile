CCC        =g++
CFLAGS   +=-L/sw/gcc-${GCC4_V}/lib -static-libstdc++ -std=c++11 -pedantic -Wall -Wextra
INCLUDE  = -I./objects
SDLFLAGS += -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer 
OBJECTS = main.cpp  GameCard.o HeroCard.o Card.o menu.o game.o Button.o Slider.o Textbox.o Checkbox.o Functions.o Window.o music.o SGS.o CardList.o FrameRateFixer.o Timer.o PopupText.o Player.o Settings.o ClickBox.o

SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring mingw, $(SYS)))
 # mingw
ALLFLAGS += $(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) -lmingw32 $(SDLFLAGS) 
 else 
 # else solaris
ALLFLAGS += $(CCC) $(INCLUDE) $(CFLAGS) $(OBJECTS) $(SDLFLAGS)
endif


all: $(OBJECTS)
		@ echo
		@ echo execute skapas
		@$(ALLFLAGS) -o "SanGuoSha"
		@ echo
		@ echo Filen lyckades att skapa
		@ echo Filnamnet ar SanGuoSha
		@ echo

		
FrameRateFixer.o: FrameRateFixer.cpp FrameRateFixer.h
		@ echo FrameRateFixer.o skapas
		@$(CCC) $(CFLAGS) -c FrameRateFixer.cpp $(SDLFLAGS)
		
Functions.o: Functions.cpp Functions.h
		@ echo Functions.o skapas
		@$(CCC) $(CFLAGS) -c Functions.cpp $(SDLFLAGS)
		
music.o: music.h music.cpp
		@ echo music.o skapas
		@$(CCC) $(CFLAGS) -c music.cpp $(SDLFLAGS)
		
menu.o: menu.cpp menu_commands.cpp SGS.h
		@ echo Menu.o skapas
		@$(CCC) $(INCLUDE) $(CFLAGS) -c menu.cpp $(SDLFLAGS)
		
game.o: game.cpp game_commands.cpp card_commands.cpp SGS.h rulebook.cpp
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
			
GameCard.o: ./objects/GameCard.h ./objects/GameCard.cpp
		@ echo GameCard.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/GameCard.cpp $(SDLFLAGS)
		
HeroCard.o: ./objects/HeroCard.h ./objects/HeroCard.cpp
		@ echo HeroCard.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/HeroCard.cpp $(SDLFLAGS)

CardList.o: ./objects/CardList.h ./objects/CardList.cpp
		@ echo CardList.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/CardList.cpp $(SDLFLAGS)

Card.o: ./objects/Card.h ./objects/Card.cpp
		@ echo Card.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/Card.cpp $(SDLFLAGS)
	
PopupText.o: ./objects/PopupText.h ./objects/PopupText.cpp
		@ echo PopupText.o skapas
		@$(CCC) $(CFLAGS) -c ./objects/PopupText.cpp $(SDLFLAGS)
		
ClickBox.o: ./objects/ClickBox.h ./objects/ClickBox.cpp
		@ echo ClickBox.o 
		@ $(CCC) $(CFLAGS) -c ./objects/ClickBox.cpp $(SDLFLAGS)
	
Timer.o: Timer.h Timer.cpp
	@ echo Timer.o skapas
	@$(CCC) $(CFLAGS) -c Timer.cpp $(SDLFLAGS)
		
Settings.o: Settings.cpp Settings.h
			@ echo Settings.o skapas
			@$(CCC) $(CFLAGS) -c Settings.cpp $(SDLFLAGS)

clean:
		@ rm -rf *.o

zap: clean
		@ rm -rf "SanGuoSha" *~ stderr.txt stdout.txt
		
