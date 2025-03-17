#include "PhysicalEntity.h"
#include "Utils.h"

void PhysicalEntity::OnInitialize()
{
}

void PhysicalEntity::Fall(float deltaTime)
{
	float gravity = 9.81f;
	float speed = 50.f;

	sf::Vector2f pPos = GetPosition();
	sf::Vector2f ColliderSize = GetColliderSize();
	mGravitySpeed += speed * gravity * deltaTime;
	mBoxCollider->yMin += mGravitySpeed * deltaTime;
	mBoxCollider->yMax = mBoxCollider->yMin + ColliderSize.y;
	pPos.y += mGravitySpeed * deltaTime;
	SetPosition(pPos.x, pPos.y);
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
	if (c1.xMin < mBoxCollider->xMax && c1.xMax >  mBoxCollider->xMin &&
		c1.yMin < mBoxCollider->yMax && c1.yMax >  mBoxCollider->yMin)
	{
		sf::Vector2f posThis = GetColliderPos();
		sf::Vector2f sizeThis = GetColliderSize();

		float widthOther = c1.xMax - c1.xMin;
		float heightOther = c1.yMax - c1.yMin;
		sf::Vector2f posOther = sf::Vector2f(c1.xMin + widthOther / 2, c1.yMin + heightOther / 2);

		float deltaX = posOther.x - posThis.x;
		float deltaY = posOther.y - posThis.y;
		float intersectX = abs(deltaX) - (widthOther / 2 + sizeThis.x / 2);
		float intersectY = abs(deltaY) - (heightOther / 2 + sizeThis.y / 2);

		sf::Vector2f pPos = GetPosition(0.5f, 0.5f);
		if (intersectX < 0.f && intersectY < 0.f) {
			if (intersectX > intersectY) {
				if (deltaX > 0.f) {
					mBoxCollider->xMin = c1.xMin - sizeThis.x;
					mBoxCollider->xMax = mBoxCollider->xMin + mBoxCollider->xSize;
					pPos.x = mBoxCollider->xMax - GetWidth() / 2;
					state = LEFT;
				}
				else {
					mBoxCollider->xMin = c1.xMax;
					mBoxCollider->xMax = mBoxCollider->xMin + mBoxCollider->xSize;
					pPos.x = mBoxCollider->xMin + GetWidth() / 2;
					state = RIGHT;
				}
			}
			else {
				if (deltaY > 0.f) 
				{
					mBoxCollider->yMin = c1.yMin - mBoxCollider->ySize;
					mBoxCollider->yMax = c1.yMin;
					pPos.y = mBoxCollider->yMax - GetHeight() / 2;
					mGravitySpeed = 0;
					mNbrJump = 2;
					state = TOP;
				}
				else {
					mBoxCollider->yMin = c1.yMax;
					mBoxCollider->yMax = mBoxCollider->yMin + mBoxCollider->ySize;
					pPos.y = mBoxCollider->yMin + GetHeight() / 2;
					mGravitySpeed = 0;
					mNbrJump = 2;
					state = BOTTOM;
				}
			}
		}
		SetPosition(pPos.x, pPos.y);
		return true;
	}
	else
	{
		state = None;
	}
	return false;
}