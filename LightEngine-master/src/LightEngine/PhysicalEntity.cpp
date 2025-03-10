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

