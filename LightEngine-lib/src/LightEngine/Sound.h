#pragma once
#include <SFML/Audio.hpp>

class Sound
{
private:
	sf::SoundBuffer mSoundBuffer;
	sf::Sound mSound;

public:
	Sound(const char* path);
	
	void Play();
	void Pause();
	void Stop();
	void SetLoop(bool isLoop);
	void SetVolume(float volume);
};

