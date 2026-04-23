#pragma once
#include <SFML/Audio.hpp>

class Music
{
private:
	sf::Music mMusic;

public:
	Music(const char* path);

	void Play();
	void Pause();
	void Stop();
	void SetLoop(bool isLoop);
	void SetVolume(float volume);
};