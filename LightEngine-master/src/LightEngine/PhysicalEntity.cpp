#include "PhysicalEntity.h"

void PhysicalEntity::OnInitialize()
{
}

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

bool PhysicalEntity::IsColliding(const AABBCollider& c1)
{

	if (c1.xMin < mBoxCollider->xMax &&
		c1.xMax >  mBoxCollider->xMin &&
		c1.yMin < mBoxCollider->yMax &&
		c1.yMax >  mBoxCollider->yMin)
	{
		mGravitySpeed = 0;
		return true;
	}
	else
	{
		return false;
	}
	/*if (c1.xMax < c2.xMin || c1.xMin > c2.xMax)
	{
		return false;
	}
	if (c1.yMax < c2.yMin || c1.yMin > c2.yMax)
	{
		return false;
	}
	return true;*/
}

