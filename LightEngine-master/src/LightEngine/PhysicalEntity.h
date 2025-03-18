#pragma once
#include "Entity.h"
#include <iostream>

class PhysicalEntity : public Entity
{

protected:
	float mNbrJump = 2;
	bool mGravity = true;
	float mGravitySpeed = 0.f;

public:
	CollisionFace GetState() { return state; }
	void SetStateCollision(CollisionFace pState) { state = pState; }
	float GetGravitySpeed() { return mGravitySpeed; }
	void SetGravitySpeed(float pSpeed) { mGravitySpeed = pSpeed; }
	void OnInitialize() override;
	void Fall(float deltaTime);
	void OnUpdate() override;
	bool IsColliding(const AABBCollider& c1);
	void Repulse(const AABBCollider&);
};