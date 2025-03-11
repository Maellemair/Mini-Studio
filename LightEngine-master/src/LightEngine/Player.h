#pragma once
#include "Entity.h"
#include <iostream>

class Player : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;
	bool isJumping = false;
	int jumpCount = 0;

	
public:
	void Fall(float deltaTime);
	void Jump();
	void Move();
	void OnUpdate() override;
};

