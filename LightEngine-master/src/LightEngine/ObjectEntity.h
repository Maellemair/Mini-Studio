#pragma once
#include "Entity.h"

class ObjectEntity : public Entity
{
public:
	void OnCollision(Entity* collidedWith) override;
};

