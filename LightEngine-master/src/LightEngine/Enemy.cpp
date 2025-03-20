#include "Enemy.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"

void Enemy::OnInitialize()
{
	SetTag(16);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_Ennemy"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(53, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_Ennemy"], "../../../res/Enemy.json", mShape);
	
	mpStateMachine = new StateMachine<Enemy>(this, State::Count);
	//EVIL
	{
		Action<Enemy>* pEvil = mpStateMachine->CreateAction<EnemyAction_Evil>(State::EVIL);

		//-> KICK
		{
			auto transition = pEvil->CreateTransition(State::KICK);

			auto condition = transition->AddCondition<EnemyCondition_IsColliding>(true);
		}

		//-> HIT
		{
			auto transition = pEvil->CreateTransition(State::HIT);

			//transition->AddCondition<PlayerCondition_isGround>(false);
		}
	}

	//KICK
	{
		Action<Enemy>* pKick = mpStateMachine->CreateAction<EnemyAction_Evil>(State::KICK);

		//-> EVIL
		{
			auto transition = pKick->CreateTransition(State::EVIL);

			//transition->AddCondition<PlayerCondition_isGround>(true);
		}

	}

	//HIT
	{
		Action<Enemy>* pHit = mpStateMachine->CreateAction<EnemyAction_Hit>(State::HIT);

		//-> EVIL
		{
			auto transition = pHit->CreateTransition(State::EVIL);

			//transition->AddCondition<PlayerCondition_IsMoving>(false);
		}
	}

	//NICE
	{
		Action<Enemy>* pNice = mpStateMachine->CreateAction<EnemyAction_Nice>(State::NICE);
	}

	mpStateMachine->SetState(State::EVIL);
	mState = (Enemy::State)mpStateMachine->GetCurrentState();
}

void Enemy::OnCollision(Entity* collidedWith)
{

}

const char* Enemy::GetStateName(State state) const
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

void Enemy::OnUpdate()
{
	mpStateMachine->Update();
}

