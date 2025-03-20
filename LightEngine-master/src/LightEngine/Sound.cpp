#include "Sound.h"

#include <iostream>

void Sound::Load(const char* path)
{
	if (!mBuffer.loadFromFile(path))
	{
		std::cout << "Erreur de chargement de la music" << std::endl;
	}
	mSound.setBuffer(mBuffer);
	mSound.setVolume(50);
}

void Sound::Play()
{
	mSound.play();
}

void Sound::LoadAndPlay(const char* path)
{
	Load(path);
	Play();
}
