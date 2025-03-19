#pragma once
#include <SFML/Audio.hpp>

class Music
{
	sf::Music mMusic;

public:
	void Load(const char* path, int pVolume);
	void Play();
	void Pause();
	void PausePlay();
};

