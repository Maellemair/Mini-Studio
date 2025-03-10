#pragma once
#include "Entity.h"

class PhysicalEntity : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;

	void Fall(float deltaTime);
	void Jump();
};

