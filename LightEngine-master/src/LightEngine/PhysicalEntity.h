#pragma once
#include "Entity.h"
#include <iostream>

enum CollisionSide {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	None,
};

class PhysicalEntity : public Entity
{
	CollisionSide state = None;
protected:
	float mNbrJump = 2;
	bool mGravity = true;
	float mGravitySpeed = 0.f;

public:
	void OnInitialize() override;
	void Fall(float deltaTime);
	void OnUpdate() override;
	bool IsColliding(const AABBCollider& c1);
};

