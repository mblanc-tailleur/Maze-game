#include "Sound.h"

Sound::Sound(const char* path)
{
	mSoundBuffer.loadFromFile(path);
	mSound.setBuffer(mSoundBuffer);
}

void Sound::Play()
{
	mSound.play();
}

void Sound::Pause()
{
	mSound.pause();
}

void Sound::Stop()
{
	mSound.stop();
}

void Sound::SetLoop(bool isLoop)
{
	mSound.setLoop(isLoop);
}

void Sound::SetVolume(float volume)
{
	mSound.setVolume(volume);
}