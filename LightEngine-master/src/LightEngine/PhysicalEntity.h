#pragma once
#include "Entity.h"
#include <iostream>

class PhysicalEntity : public Entity
{

protected:
	float mNbrJump = 2;
	bool mGravity = true;
	float mGravitySpeed = 0.f;
	Entity* ColliderEntity = nullptr;

public:
	CollisionFace GetState() { return state; }
	void SetStateCollision(CollisionFace pState) { state = pState; }
	void SetColliderEntity(Entity* other) { ColliderEntity = other; }
	float GetGravitySpeed() { return mGravitySpeed; }
	void SetGravitySpeed(float pSpeed) { mGravitySpeed = pSpeed; }
	void OnInitialize() override;
	void Fall(float deltaTime);
	void OnUpdate() override;
	void Repulse(Entity* c1);
};