#include "EnemyVolant.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"


void EnemyVolant::OnInitialize()
{
	mpStateMachine = new StateMachine<EnemyVolant>(this, State::Count);

	//State
	{
		//EVIL
		{
			Action<EnemyVolant>* pEvil = mpStateMachine->CreateAction<EnemyVolantAction_Evil>(State::EVIL);

			//-> SHOOT
			{
				auto transition = pEvil->CreateTransition(State::SHOOT);

				transition->AddCondition<EnemyVolantCondition_isTakingDamage>(false);
				transition->AddCondition<EnemyVolantCondition_isAttacking>(true);
			}

			//-> HIT
			{
				auto transition = pEvil->CreateTransition(State::HIT);

				transition->AddCondition<EnemyVolantCondition_isTakingDamage>(true);
				transition->AddCondition<EnemyVolantCondition_isAttacking>(false);
			}
		}

		//SHOOT
		{
			Action<EnemyVolant>* pKick = mpStateMachine->CreateAction<EnemyVolantAction_Shoot>(State::SHOOT);

			//-> EVIL
			{
				auto transition = pKick->CreateTransition(State::EVIL);

				transition->AddCondition<EnemyVolantCondition_isAttacking>(false);
			}

		}

		//HIT
		{
			Action<EnemyVolant>* pHit = mpStateMachine->CreateAction<EnemyVolantAction_Hit>(State::HIT);

			//-> EVIL
			{
				auto transition = pHit->CreateTransition(State::EVIL);

				transition->AddCondition<EnemyVolantCondition_isTakingDamage>(false);
				transition->AddCondition<EnemyVolantCondition_isDead>(false);
			}

			//-> NICE
			{
				auto transition = pHit->CreateTransition(State::NICE);

				transition->AddCondition<EnemyVolantCondition_isTakingDamage>(false);
				transition->AddCondition<EnemyVolantCondition_isDead>(true);
			}
		}

		//NICE
		{
			Action<EnemyVolant>* pNice = mpStateMachine->CreateAction<EnemyVolantAction_Nice>(State::NICE);
		}
	}

	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_EnnemyVolant"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(32, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_EnnemyVolant"], "../../../res/EnemyVolant.json", mShape);

	mpStateMachine->SetState(State::EVIL);
	mState = (EnemyVolant::State)mpStateMachine->GetCurrentState();

}

const char* EnemyVolant::GetStateName(State state) const
{
	switch (state)
	{
	case EVIL: return "Evil";
	case SHOOT: return "Shoot";
	case HIT: return "Hit";
	case NICE: return "Nice";
	default: return "Unknown";
	}
}

void EnemyVolant::Tracking(float pPosX)
{
	float direction = (pPosX - GetPosition().x) / abs(pPosX - GetPosition().x);
	SetDirection(direction, 0 ,50);
	isTraking = true;
}

void EnemyVolant::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	mState = (EnemyVolant::State)mpStateMachine->GetCurrentState();

	mpStateMachine->Update();
	Enemy::OnUpdate();
}
