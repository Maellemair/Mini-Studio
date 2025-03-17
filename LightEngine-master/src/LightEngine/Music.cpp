#include "Music.h"

#include <iostream>

void Music::Load(const char* path)
{
	if (!mMusic.openFromFile(path))
	{
		std::cout << "Erreur de chargement de la music" << std::endl;
	}
	mMusic.setVolume(10);
	mMusic.setLoop(true);
}

void Music::Play()
{
	mMusic.play();
	std::cout << "Music is playing" << std::endl;
}

void Music::Pause()
{
	mMusic.pause();
	std::cout << "Music is paused" << std::endl;
}

void Music::PausePlay()
{
	if (mMusic.getStatus() == sf::Music::Status::Playing)
	{
		mMusic.pause();
		std::cout << "Music is paused" << std::endl;
		std::cout << mMusic.getStatus() << std::endl;
		return;
	}
	else
	{
		mMusic.play();
		std::cout << "Music is playing" << std::endl;
		std::cout << mMusic.getStatus() << std::endl;
		return;
	}
}
