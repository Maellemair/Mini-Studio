#pragma once
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;
	bool isJumping = false;
	int jumpCount = 0;
	int MaxLife = 3;
	int Life = MaxLife;
	
public:
	void Fall(float deltaTime);
	void Jump();
	void Move();
	void TakeHit();
	void OnUpdate() override;
};

