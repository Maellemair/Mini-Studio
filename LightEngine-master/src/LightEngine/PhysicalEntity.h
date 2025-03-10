#pragma once
#include "Entity.h"

struct AABBCollider
{
	float xMin, yMin;
	float xMax, yMax;
};

class PhysicalEntity : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;

	void Fall(float deltaTime);
	void Jump();

	bool IsColliding(const AABBCollider& c1, const AABBCollider& c2);
};

