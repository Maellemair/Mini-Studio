#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class Texture;

class Enemy : public PhysicalEntity, public Animation
{
	enum State
	{
		EVIL,
		KICK,
		HIT,
		NICE,
		Count
	};

	State mState;

    Animation* animEnemy;
    StateMachine<Enemy>* mpStateMachine;
public:
    void OnInitialize() override;
    void OnCollision(Entity* collidedWith) override;
	const char* GetStateName(State state) const;
    const AABBCollider* GetCollider() { return mBoxCollider; }
	void OnUpdate() override;

};