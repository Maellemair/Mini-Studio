#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Sound;

class Player : public PhysicalEntity
{
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;

	Sound* mSound;

public:
	void OnInitialize() override;
	void Move(float deltaTime, int key);
	void Reset();
	void Jump();
};

