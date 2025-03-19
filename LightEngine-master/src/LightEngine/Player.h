#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class Texture;
class Sound;
class Bullets;

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
	Animation* animPlayer;
	StateMachine<Player>* mpStateMachine;
	Sound* mSound;	
	int lastDirection = 1;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetState(State pState);
	const char* GetStateName(State state) const;
	int getLastDirection();
	void setLastDirection(int dir);
	void Move(int key);
	void Reset();
	void Jump();
	void TakeHit();
	void Dash(float deltaTime);

	int MaxLife = 3;
	int mLife = MaxLife;
	float dashTime = 0.2f;
	float dashTimer = 0.0f;
	float dashCooldown;
	float shootCooldown = 0.5f;
	float invicibilityTime = 0.0f;
	float repulsionTimer = 0.0f;

protected:
	friend class PlayerAction_Fall;
	friend class PlayerAction_Idle;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Walk;
};

