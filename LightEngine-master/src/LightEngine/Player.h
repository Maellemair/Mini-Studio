#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Texture;

enum State
{
	WALK,
	JUMP,
	FALL,
	SHOOT,
	IDLE,
	NONE
};

class Player : public PhysicalEntity, public Animation
{	
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

