#pragma once
#include "Entity.h"

class ObjectEntity : public Entity
{

public:
	const AABBCollider* GetCollider() { return mBoxCollider; }
	virtual ObjectEntity* Clone(float height, float width, float posX, float posY);
};

