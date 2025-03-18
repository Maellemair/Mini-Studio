#include "ObjectEntity.h"
#include <iostream>

ObjectEntity* ObjectEntity::Clone(float height, float width, float posX, float posY)
{
	return nullptr;
}

bool ObjectEntity::IsColliding(const AABBCollider& c1)
{
	if (c1.xMin < mBoxCollider->xMax &&
		c1.xMax >  mBoxCollider->xMin &&
		c1.yMin < mBoxCollider->yMax &&
		c1.yMax >  mBoxCollider->yMin)
	{
		return true;
	}
	else
	{
		return false;
	}
}
