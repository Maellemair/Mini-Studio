#include "PhysicalEntity.h"

void PhysicalEntity::Fall(float deltaTime)
{
	float gravity = 9.81f;

	float pPosY = GetPosition().y;
	mGravitySpeed += gravity * deltaTime;
	pPosY += mGravitySpeed * deltaTime;
}

void PhysicalEntity::Jump()
{
	mGravitySpeed -= 100;
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

