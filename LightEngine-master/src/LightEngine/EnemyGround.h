#pragma once
#include "Enemy.h"

template<typename T>
class StateMachine;
class Texture;

class EnemyGround : public Enemy
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
	StateMachine<EnemyGround>* mpStateMachine;

	float mDirectionKick = 0;
	sf::Clock animKickTime;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	const char* GetStateName(State state) const;
	void Attack(float pDirection) override;

protected:
	friend class EnemyGroundAction_Evil;
	friend class EnemyGroundAction_Kick;
	friend class EnemyGroundAction_Hit;
	friend class EnemyGroundAction_Nice;

};