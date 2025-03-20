#include "EnemyVolant.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"


void EnemyVolant::OnInitialize()
{

	//EVIL
	{
		Action<EnemyVolant>* pEvil = mpStateMachine->CreateAction<EnemyVolantAction_Evil>(State::EVIL);

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
		Action<EnemyVolant>* pKick = mpStateMachine->CreateAction<EnemyVolantAction_Kick>(State::KICK);

		//-> EVIL
		{
			auto transition = pKick->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyCondition_isAttacking>(false);
		}

	}

	//HIT
	{
		Action<EnemyVolant>* pHit = mpStateMachine->CreateAction<EnemyVolantAction_Hit>(State::HIT);

		//-> EVIL
		{
			auto transition = pHit->CreateTransition(State::EVIL);

			transition->AddCondition<EnemyCondition_isTakingDamage>(false);
		}
	}

	//NICE
	{
		Action<EnemyVolant>* pNice = mpStateMachine->CreateAction<EnemyVolantAction_Nice>(State::NICE);
	}

	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_EnnemyVolant"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(53, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_EnnemyVolant"], "../../../res/EnemyVolant.json", mShape);

	mpStateMachine = new StateMachine<EnemyVolant>(this, State::Count);
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

void EnemyVolant::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	mState = (EnemyVolant::State)mpStateMachine->GetCurrentState();
	const char* stateName = GetStateName(mState);
	Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);
}
