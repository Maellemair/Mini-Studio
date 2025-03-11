#pragma once
#include "Entity.h"
#include <iostream>

class PhysicalEntity : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;

public:
	void OnInitialize() override;
	void Fall(float deltaTime);
	void Jump();
	void OnUpdate() override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	bool IsColliding(const AABBCollider& c1);
};

