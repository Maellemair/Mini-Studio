#include "PhysicalEntity.h"
#include <iostream>


void PhysicalEntity::Fall(float deltaTime)
{
	if (!mGravity) return;
	
	float gravity = 9.81f;
	float speed = 10.f;


	sf::Vector2f pPos = GetPosition();
	mGravitySpeed += speed * gravity * deltaTime;
	pPos.y += mGravitySpeed * deltaTime;
	SetPosition(pPos.x, pPos.y);

	//std::cout << "GravitySpeed: " << mGravitySpeed << " | Position Y: " << mPosition.y << std::endl;
}

void PhysicalEntity::Jump()
{
	EnableGravity(true);
	mGravitySpeed = -200;
	std::cout << "Jump" << std::endl;
}

void PhysicalEntity::EnableGravity(bool value)
{
	mGravity = value;
	if (!mGravity)
		mGravitySpeed = 0.f;
}

//void PhysicalEntity::BottomEdgeCollision(float groundY)
//{
//	if (GetPosition().y + 49 >= groundY)
//	{
//		EnableGravity(false);
//		SetPosition(GetPosition().x, groundY - 50);
//	}
//}

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

void PhysicalEntity::OnUpdate()
{
	float dt = GetDeltaTime();
	Fall(dt);
	//std::cout << "GetDeltaTime(): " << dt << std::endl;
}