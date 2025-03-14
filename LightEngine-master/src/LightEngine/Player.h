#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Player : public PhysicalEntity
{
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;

public:
	void OnInitialize() override;
	void Move(int key);
	void Reset();
	void Jump();
};

