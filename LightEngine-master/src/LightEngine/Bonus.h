#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Bonus : public PhysicalEntity
{

public:
	virtual void Update() {};
	void OnCollision(Entity* collidedWith) override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	void OnUpdate() override;
};

