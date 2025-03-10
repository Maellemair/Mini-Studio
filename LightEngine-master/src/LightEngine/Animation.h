#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
	sf::Image mImages[4];
	int mCurrentIndex = 0;
	float mDuration = 100.f;

public:
	void Update(float dt);
};

