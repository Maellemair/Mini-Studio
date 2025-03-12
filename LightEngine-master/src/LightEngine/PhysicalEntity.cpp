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
					pPos.x = c1.xMin - GetWidth() / 2;
					mBoxCollider->xMin = c1.xMin - sizeThis.x;
					mBoxCollider->xMax = mBoxCollider->xMin + sizeThis.x;
					state = LEFT;
				}
				else {
					pPos.x = c1.xMax + GetWidth() / 2;
					mBoxCollider->xMin = c1.xMax;
					mBoxCollider->xMax = mBoxCollider->xMin + sizeThis.x;
					state = RIGHT;
				}
			}
			else{
				if (deltaY > 0.f) {
					pPos.y = c1.yMin - GetHeight() / 2;
					mBoxCollider->yMin = c1.yMin - GetHeight();
					mBoxCollider->yMin = mBoxCollider->yMin + sizeThis.y;
					state = TOP;
					mNbrJump = 0;
					mGravitySpeed = 0;
				}
				else {
					pPos.y = c1.yMax + GetHeight() / 2;
					mBoxCollider->yMin = c1.yMin;
					mBoxCollider->yMin = mBoxCollider->yMin + sizeThis.y;
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

