#include "EnemyGround.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"

void EnemyGround::OnInitialize()
{
	//EVIL
	{
		Action<Enemy>* pEvil = mpStateMachine->CreateAction<EnemyAction_Evil>(State::EVIL);

		//-> KICK
		{
			auto transition = pEvil->CreateTransition(State::KICK);

			transition->AddCondition<EnemyCondition_isTakingDamage>(false);
			transition->AddCondition<EnemyCondition_isAttacking>(true);
		}

		//-> HIT
		{
			auto transition = pEvil->CreateTransition(State::HIT);

			transition->AddCondition<EnemyCondition_isTakingDamage>(true);
			transition->AddCondition<EnemyCondition_isAttacking>(false);
		}
	}

	//KICK
	{
		Action<Enemy>* pKick = mpStateMachine->CreateAction<EnemyAction_Kick>(State::KICK);

		//-> EVIL
		{
			auto transition = pKick->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyCondition_isAttacking>(false);
		}

	}

	//HIT
	{
		Action<Enemy>* pHit = mpStateMachine->CreateAction<EnemyAction_Hit>(State::HIT);

		//-> EVIL
		{
			auto transition = pHit->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyCondition_isTakingDamage>(false);
		}
	}

	//NICE
	{
		Action<Enemy>* pNice = mpStateMachine->CreateAction<EnemyAction_Nice>(State::NICE);
	}

	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_EnnemySol"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(53, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_EnnemySol"], "../../../res/Enemy.json", mShape);
	
	mpStateMachine = new StateMachine<EnemyGround>(this, State::Count);
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

void EnemyGround::Kick(float pDirection)
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
	const char* stateName = GetStateName(mState);
	Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);
}

