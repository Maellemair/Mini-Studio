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
	bool isTraking;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void Attack(float direction) override { isAttacking = true; }
	const char* GetStateName(State state) const;
	void Tracking(float pPosX);
	void SetIsTracking(bool pState) { isTraking = pState; }

protected:
	friend class EnemyVolantAction_Evil;
	friend class EnemyVolantAction_Shoot;
	friend class EnemyVolantAction_Hit;
	friend class EnemyVolantAction_Nice;

};

