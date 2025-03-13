#include "ObjectEntity.h"
#include <iostream>

void ObjectEntity::OnInitialize()
{
}

bool ObjectEntity::IsColliding(const AABBCollider& c1)
{
	if (c1.xMin < mBoxCollider->xMax &&
		c1.xMax >  mBoxCollider->xMin &&
		c1.yMin < mBoxCollider->yMax &&
		c1.yMax >  mBoxCollider->yMin)
	{
		std::cout << "Test" << std::endl;
		return true;
	}
	else
	{
		return false;
	}/*
	if (c1.xMax < mBoxCollider->xMin || c1.xMin > mBoxCollider->xMax)
	{
		return false;
	}
	if (c1.yMax < mBoxCollider->yMin || c1.yMin > mBoxCollider->yMax)
	{
		return false;
	}
	return true;*/
}
