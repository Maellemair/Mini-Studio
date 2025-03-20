#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Texture;
class Enemy;

class Bullets : public PhysicalEntity
{
	Enemy* pEnemy;
	float deltaTime = GameManager::Get()->GetDeltaTime();
	float lifeTime = 1.5f;
	float lifeTimer = 0.0f;
public:
	void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override;
	const AABBCollider* GetCollider() { return mBoxCollider; }
	void Update();
};
