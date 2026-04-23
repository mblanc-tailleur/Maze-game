#include "Music.h"

Music::Music(const char* path)
{
	mMusic.openFromFile(path);
}

void Music::Play()
{
	mMusic.play();
}

void Music::Pause()
{
	mMusic.pause();
}

void Music::Stop()
{
	mMusic.stop();
}

void Music::SetLoop(bool isLoop)
{
	mMusic.setLoop(isLoop);
}

void Music::SetVolume(float volume)
{
	mMusic.setVolume(volume);
}
