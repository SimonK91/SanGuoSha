#ifndef MUSIC_H
#define MUSIC_H

#include "Functions.h"

class Music
{
private:

	Mix_Music* music = nullptr;
	std::vector<Mix_Chunk*> soundEffects;

public:
	Music() = delete;
	Music(const std::string& musicFile){ loadMusic(musicFile); }
	~Music();
	
	int getVolume();
	int getEffectVolume();
	void setVolume(const int& volume);
	void setEffectVolume(const int& volume);
	void play();
	void pause();
	void stop();
	void loadMusic(const std::string& musicFile);
	void loadSoundEffect(const std::string& effects);
	void playSoundEffect(const unsigned& index);
};

#endif
