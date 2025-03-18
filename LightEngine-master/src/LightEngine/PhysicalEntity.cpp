#include "PhysicalEntity.h"
#include <iostream>

#include "Utils.h"

void PhysicalEntity::OnInitialize()
{
}

void PhysicalEntity::Fall(float deltaTime)
{
	if (!mGravity) return;
	
	float gravity = 9.81f;
	float speed = 50.f;


	sf::Vector2f pPos = GetPosition();
	sf::Vector2f ColliderSize = GetColliderSize();
	mGravitySpeed += speed * gravity * deltaTime;
	mBoxCollider->yMin += mGravitySpeed * deltaTime;
	mBoxCollider->yMax = mBoxCollider->yMin + ColliderSize.y;
	pPos.y += mGravitySpeed * deltaTime;
	SetPosition(pPos.x, pPos.y);

	//std::cout << "GravitySpeed: " << mGravitySpeed << " | Position Y: " << mPosition.y << std::endl;
}

void PhysicalEntity::OnUpdate()
{
	float dt = GetDeltaTime();

	if (state != TOP)
	{
		Fall(dt);
	}
}

bool PhysicalEntity::IsColliding(const AABBCollider& c1)
{
    if (c1.xMin < mBoxCollider->xMax && c1.xMax > mBoxCollider->xMin &&
        c1.yMin < mBoxCollider->yMax && c1.yMax > mBoxCollider->yMin)
    {
        return true;
    }
    return false;
}

void PhysicalEntity::Repulse(const AABBCollider& c1)
{
    if(IsColliding(c1))
    {
        sf::Vector2f posThis = GetColliderPos();
        sf::Vector2f sizeThis = GetColliderSize();

        float widthOther = c1.xMax - c1.xMin;
        float heightOther = c1.yMax - c1.yMin;
        sf::Vector2f posOther = sf::Vector2f(c1.xMin + widthOther / 2, c1.yMin + heightOther / 2);

        sf::Vector2f distance = sf::Vector2f(posOther.x - posThis.x, posOther.y - posThis.y);
        float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

        if (sqrLength == 0.0f)
            return;

        float length = std::sqrt(sqrLength);

        float intersectX = (widthOther / 2 + sizeThis.x / 2) - abs(distance.x);
        float intersectY = (heightOther / 2 + sizeThis.y / 2) - abs(distance.y);

        if (intersectX > 0.f && intersectY > 0.f)
        {
            if (intersectX < intersectY)
            {
                if (distance.x > 0.f)
                {
                    SetPosition(GetPosition().x - intersectX, GetPosition().y);
                    state = LEFT;
                }
                else
                {
                    SetPosition(GetPosition().x + intersectX, GetPosition().y);
                    state = RIGHT;
                }
            }
            else
            {
                if (distance.y > 0.f)
                {
                    SetPosition(GetPosition().x, GetPosition().y - intersectY);
                    state = TOP;
                    mGravitySpeed = 0;
                    mNbrJump = 0;
                }
                else
                {
                    SetPosition(GetPosition().x, GetPosition().y + intersectY);
                    state = BOTTOM;
                }
            }

            mBoxCollider->xMin = GetPosition().x - sizeThis.x / 2;
            mBoxCollider->xMax = GetPosition().x + sizeThis.x / 2;
            mBoxCollider->yMin = GetPosition().y - sizeThis.y / 2;
            mBoxCollider->yMax = GetPosition().y + sizeThis.y / 2;
        }
    }
    else
    {
        state = None;
    }
}
