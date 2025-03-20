#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class SampleScene;
class Texture;

class Enemy : public PhysicalEntity, public Animation
{
protected:
	bool isTakingDamage = false;
	bool isAttacking = false;
	sf::Clock animHitTime;
    Animation* animEnemy;

public:
    void OnInitialize() override;
	void OnCollision(Entity* collidedWith) override { }
	void Hit();
	void Kick(float pDirection);
	bool GetIsTakingDamage() { return isTakingDamage; }
	bool GetIsAttacking() { return isAttacking; }
    const AABBCollider* GetCollider() { return mBoxCollider; }
	void OnUpdate() override;

protected:
	friend class EnemyAction_Evil;
	friend class EnemyAction_Kick;
	friend class EnemyAction_Hit;
	friend class EnemyAction_Nice;

};