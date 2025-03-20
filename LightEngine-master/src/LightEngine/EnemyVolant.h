#pragma once
#include "Enemy.h"

template<typename T>
class StateMachine;
class Texture;

class EnemyVolant : public Enemy
{
	enum State
	{
		EVIL,
		SHOOT,
		HIT,
		NICE,
		Count
	};

	State mState;
	StateMachine<EnemyVolant>* mpStateMachine;
	sf::Clock animShootTime;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	const char* GetStateName(State state) const;

protected:
	friend class EnemyVolantAction_Evil;
	friend class EnemyVolantAction_Shoot;
	friend class EnemyVolantAction_Hit;
	friend class EnemyVolantAction_Nice;

};

