#include "music.h"
#include <stdexcept>

using namespace std;

Music::~Music(){
	Mix_FreeMusic( music );
	for(Mix_Chunk * se : soundEffects)
	{
		Mix_FreeChunk(se);
	}
	soundEffects.clear();
}

 void Music::play()
{
	if(Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic( music, -1 );			//vilken musik, hur många ggr -1 = inf
	}
}

void Music::pause()
{
	if(Mix_PausedMusic() == 0)
	{
		Mix_PauseMusic();
	}
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::loadMusic(const std::string& musicFile){
	if(music != nullptr)
	{
		Mix_FreeMusic( music );
	}
	music = Mix_LoadMUS( musicFile.c_str() );
	
	if(!music)
		throw std::runtime_error("music file could not be opened: " + musicFile);
}

void Music::setVolume(const int& volume)
{
	Mix_VolumeMusic((volume*128) / 100);
}

void Music::setEffectVolume(const int& volume)
{
	for(Mix_Chunk* se : soundEffects)
	{
		Mix_VolumeChunk(se,( volume * 128 ) / 100 );
	}
}

int Music::getVolume(){
	return (Mix_VolumeMusic(-1)*100) / 128;
}
int Music::getEffectVolume()
{
	return (Mix_VolumeChunk(soundEffects.front(),-1) * 100 ) / 128;
}

void Music::loadSoundEffect(const string& effect)
{
	Mix_Chunk * se = Mix_LoadWAV(effect.c_str());
	if(se == nullptr)
		throw std::runtime_error("failed to load soundEffectFile: " + effect);
	soundEffects.push_back(se);
}

void Music::playSoundEffect(const int& index)
{
	if(index < soundEffects.size())
		Mix_PlayChannel( -1, soundEffects.at(index), 0 );	//channel -1 = all, soundEffect, loop-times 0 => 1 play
	else
		std::cout << "soundEffect index: " << index << " is non existant" << std::endl
				  << "nEffects loaded are: " << soundEffects.size() << std::endl;
}




