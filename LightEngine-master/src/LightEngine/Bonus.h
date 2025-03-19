#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Bonus : public PhysicalEntity
{
public:

	void OnCollision(Entity* collidedWith) override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	void OnUpdate() override;
};

