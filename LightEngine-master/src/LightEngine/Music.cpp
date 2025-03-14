#include "Music.h"

#include <iostream>

void Music::Load(const char* path)
{
	if (!mMusic.openFromFile(path))
	{
		std::cout << "Erreur de chargement de la music" << std::endl;
	}
	mMusic.setVolume(50);
	mMusic.setLoop(true);
}

void Music::Play()
{
	mMusic.play();
}
