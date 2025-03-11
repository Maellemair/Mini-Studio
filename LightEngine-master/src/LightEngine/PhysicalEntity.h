#pragma once
#include "Entity.h"
#include <iostream>

struct AABBCollider
{
	float xMin, yMin;
	float xMax, yMax;
};

class PhysicalEntity : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;

public:
	void Fall(float deltaTime);
	void Jump();
	void OnUpdate() override;
	bool IsColliding(const AABBCollider& c1, const AABBCollider& c2);
};

