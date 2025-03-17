#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Bullets;

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
	void Dash(float deltaTime);

	int mLife = MaxLife;
	int MaxLife = 3;
	float dashTime = 0.2f;
	float dashTimer = 0.0f;
	float dashCooldown;
	float shootCooldown = 0.5f;
};

