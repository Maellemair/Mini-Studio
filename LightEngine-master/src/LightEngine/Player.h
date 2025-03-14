#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Player : public PhysicalEntity
{
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;
	int lastDirection = 1;
	
public:
	int getLastDirection();
	void setLastDirection(int dir);
	void Move(float deltaTime, int key);
	void Reset();
	void Jump();
	void TakeHit();
	void Shoot();
	int mLife = MaxLife;
	int MaxLife = 3;

};

