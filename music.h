#ifndef music_h
#define music_h

#include "functions.h"

class Music
{
private:

	Mix_Music* music = nullptr;
	std::vector<Mix_Chunk*> soundEffects;

public:
	Music(const std::string& musicFile  = ""){ loadMusic(musicFile); }
	~Music();
	
	int getVolume();
	int getEffectVolume();
	void setVolume(const int& volume);
	void setEffectVolume(const int& volume);
	void play();
	void pause();
	void stop();
	void loadMusic(const std::string& musicFile);
	bool loadSoundEffect(const std::string& effects);
	void playSoundEffect(const int& index);
};

#endif