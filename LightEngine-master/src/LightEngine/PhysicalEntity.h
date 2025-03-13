#pragma once
#include "Entity.h"
#include <iostream>

enum CollisionFace {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	None,
};

class PhysicalEntity : public Entity
{
	CollisionFace state = None;

protected:
	float mNbrJump = 2;
	bool mGravity = true;
	float mGravitySpeed = 0.f;

public:
	CollisionFace GetState() { return state; }
	void OnInitialize() override;
	void Fall(float deltaTime);
	void OnUpdate() override;
	bool IsColliding(const AABBCollider& c1);
};

