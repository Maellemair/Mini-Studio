#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class SampleScene;

class Bullets : public PhysicalEntity
{
	float deltaTime = GameManager::Get()->GetDeltaTime();
	float lifeTime = 1.5f;
	float lifeTimer = 0.0f;
public:
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;
};
