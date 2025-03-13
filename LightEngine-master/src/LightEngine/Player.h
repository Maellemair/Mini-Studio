#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Player : public PhysicalEntity
{
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;
	int Life = MaxLife;
	int MaxLife = 3;
public:
	void Move(float deltaTime, int key);
	void Reset();
	void Jump();
	void TakeHit();
};

