#include "PhysicalEntity.h"

void PhysicalEntity::Fall(float deltaTime)
{
	float gravity = 9.81f;
	float speed = 10.f;

	sf::Vector2f pPos = GetPosition();
	mGravitySpeed += speed * gravity * deltaTime;
	pPos.y += mGravitySpeed * deltaTime;
	SetPosition(pPos.x, pPos.y);
}

void PhysicalEntity::Jump()
{
	mGravitySpeed = -150;
	std::cout << "Jump" << std::endl;
}

void PhysicalEntity::OnUpdate()
{
	float dt = GetDeltaTime();
	Fall(dt);
}

