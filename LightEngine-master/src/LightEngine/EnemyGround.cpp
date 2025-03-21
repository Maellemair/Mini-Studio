#include "EnemyGround.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"

void EnemyGround::OnInitialize()
{
	mpStateMachine = new StateMachine<EnemyGround>(this, State::Count);

	//EVIL
	{
		Action<EnemyGround>* pEvil = mpStateMachine->CreateAction<EnemyGroundAction_Evil>(State::EVIL);

		//-> KICK
		{
			auto transition = pEvil->CreateTransition(State::KICK);

			transition->AddCondition<EnemyGroundCondition_isTakingDamage>(false);
			transition->AddCondition<EnemyGroundCondition_isAttacking>(true);
		}

		//-> HIT
		{
			auto transition = pEvil->CreateTransition(State::HIT);

			transition->AddCondition<EnemyGroundCondition_isTakingDamage>(true);
			transition->AddCondition<EnemyGroundCondition_isAttacking>(false);
		}
	}

	//KICK
	{
		Action<EnemyGround>* pKick = mpStateMachine->CreateAction<EnemyGroundAction_Kick>(State::KICK);

		//-> EVIL
		{
			auto transition = pKick->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyGroundCondition_isAttacking>(false);
		}

	}

	//HIT
	{
		Action<EnemyGround>* pHit = mpStateMachine->CreateAction<EnemyGroundAction_Hit>(State::HIT);

		//-> EVIL
		{
			auto transition = pHit->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyGroundCondition_isTakingDamage>(false);
			transition->AddCondition<EnemyGroundCondition_isDead>(false);
		}

		//-> NICE
		{
			auto transition = pHit->CreateTransition(State::NICE);

			transition->AddCondition<EnemyGroundCondition_isTakingDamage>(false);
			transition->AddCondition<EnemyGroundCondition_isDead>(true);
		}
	}

	//NICE
	{
		Action<EnemyGround>* pNice = mpStateMachine->CreateAction<EnemyGroundAction_Nice>(State::NICE);
	}

	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_EnnemySol"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(53, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_EnnemySol"], "../../../res/EnemySol.json", mShape);

	mpStateMachine->SetState(State::EVIL);
	mState = (EnemyGround::State)mpStateMachine->GetCurrentState();
}

const char* EnemyGround::GetStateName(State state) const
{
	switch (state)
	{
	case EVIL: return "Evil";
	case KICK: return "Kick";
	case HIT: return "Hit";
	case NICE: return "Nice";
	default: return "Unknown";
	}
}

void EnemyGround::Attack(float pDirection)
{
	if (pDirection == -1)
	{
		animEnemy->SetIsFacingRight(true);
	}
	else
	{
		animEnemy->SetIsFacingRight(false);
	}
	isAttacking = true;
}

void EnemyGround::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	mState = (EnemyGround::State)mpStateMachine->GetCurrentState();

	mpStateMachine->Update();
	Enemy::OnUpdate();
}

