#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class Texture;

class Sound;

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

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetState(State pState);
	const char* GetStateName(State state) const;
	void Move(int key);
	void Reset();
	void Jump();

protected:

	friend class PlayerAction_Fall;
	friend class PlayerAction_Idle;
	friend class PlayerAction_Jump;
	friend class PlayerAction_Walk;
};

