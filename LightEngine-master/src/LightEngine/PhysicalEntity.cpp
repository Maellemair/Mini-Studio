#include "PhysicalEntity.h"
#include <iostream>

float GravityAcceleration = 9.81f;

void PhysicalEntity::Fall(float deltaTime)
{
	if (!mGravity) return;
	
	mGravitySpeed += GravityAcceleration * deltaTime;
	mPosition.y += mGravitySpeed * deltaTime;

	std::cout << "GravitySpeed: " << mGravitySpeed << " | Position Y: " << mPosition.y << std::endl;

	SetPosition(mPosition.x, mPosition.y);
}

void PhysicalEntity::Jump()
{
	mGravitySpeed -= 100;
}

void PhysicalEntity::EnableGravity(bool value)
{
	mGravity = value;
	if (!mGravity)
		mGravitySpeed = 0.f;
}

bool PhysicalEntity::IsColliding(const AABBCollider& c1, const AABBCollider& c2)
{
	if (c1.xMax < c2.xMin || c1.xMin > c2.xMax)
	{
		return false;
	}
	if (c1.yMax < c2.yMin || c1.yMin > c2.yMax)
	{
		return false;
	}
	return true;
}

