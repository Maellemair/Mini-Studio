#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class Texture;

class Player : public PhysicalEntity, public Animation
{
	enum State
	{
		WALK,
		JUMP,
		FALL,
		SHOOT,
		IDLE,
		Count
	};

	State mState = IDLE;
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;
	Animation* animIdle;
	Animation* animJump;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetState(State pState);
	void Move(int key);
	void Reset();
	void Jump();
};

