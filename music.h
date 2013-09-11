#ifndef music_h
#define music_h

#include "functions.h"
//#include "SDL/SDL_mixer.h"
#include <string>

class Music
{
private:

	Mix_Music* music = nullptr;
public:
	Music(const std::string& musicFile  = "")
	{
		loadMusic(musicFile);
	}
	~Music()
	{
		Mix_FreeMusic( music ) ;
		Mix_CloseAudio();
	}
	
	void play()	
	{
		if(Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic( music, -1 );			//vilken musik, hur många ggr -1 = inf
		}
	}
	
	void pause()	//fungerar inte!
	{
		if(Mix_PausedMusic() == 0 )
		{
			Mix_Pause(-1);
		}
	}
	
	void stop()
	{
		Mix_HaltMusic();
	}
	
	void loadMusic(const std::string& musicFile){
		if(music != nullptr)
		{
			Mix_FreeMusic( music );
		}
		
		music = Mix_LoadMUS( musicFile.c_str() );
		
		//fixa sound effects efter ett tag!
	}
	
	int setVolume(const int& volume)
	{
		return Mix_VolumeMusic((volume*128) / 100);
	}
	
	int getVolume()
	{
		return (Mix_VolumeMusic(-1)*100)/128;
	}
};

#endif