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
	mSound.setPitch(1.f);
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

void Sound::SetPicth(float pitch)
{
	mSound.setPitch(pitch);
}

void Sound::RandomPitch()
{
	float pitch = 0.9f + (rand() / (float)RAND_MAX) * 0.2f;
	//std::cout << "Pitch : " << pitch << std::endl;
	mSound.setPitch(pitch);
}
