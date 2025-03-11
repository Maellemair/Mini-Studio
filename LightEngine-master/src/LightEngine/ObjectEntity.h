#pragma once
#include "Entity.h"

struct AABBCollider
{
	float xMin, yMin;
	float xMax, yMax;
};

class ObjectEntity : public Entity
{
	AABBCollider* mBoxCollider;

public:
	ObjectEntity();
	bool IsColliding(const AABBCollider& c1, const AABBCollider& c2);
};

