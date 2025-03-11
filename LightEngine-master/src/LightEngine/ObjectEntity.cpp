#include "ObjectEntity.h"


ObjectEntity::ObjectEntity()
{
	mBoxCollider->xMin = GetPosition().x - GetWidth() / 2;
	mBoxCollider->xMax = GetPosition().x + GetWidth() / 2;
	mBoxCollider->yMin = GetPosition().y - GetHeigth() / 2;
	mBoxCollider->yMax = GetPosition().y + GetHeigth() / 2;
}

bool ObjectEntity::IsColliding(const AABBCollider& c1, const AABBCollider& c2)
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
