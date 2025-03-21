#pragma once
#include <SFML/Audio.hpp>

class Sound
{
	sf::SoundBuffer mBuffer;
	sf::Sound mSound;

public:
	void Load(const char* path);
	void Play();
	void LoadAndPlay(const char* path);
	void SetPicth(float pitch);
	void RandomPitch();
};

