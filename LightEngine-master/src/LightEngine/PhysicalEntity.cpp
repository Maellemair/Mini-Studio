#include "PhysicalEntity.h"

void PhysicalEntity::Fall(float deltaTime)
{
	float gravity = 9.81f;

	sf::Vector2f pPos = GetPosition();
	mGravitySpeed += gravity * deltaTime;
	pPos.y += mGravitySpeed * deltaTime;
	SetPosition(pPos.x, pPos.y);
}

void PhysicalEntity::Jump()
{
	mGravitySpeed -= 100;
}

