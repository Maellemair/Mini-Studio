#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Texture;

class Bonus : public PhysicalEntity
{

public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	void OnUpdate() override;
};

