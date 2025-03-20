#include "Enemy.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"
#include "SampleScene.h"

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

			auto condition = transition->AddCondition<EnemyCondition_isAttacking>(true);
		}

		//-> HIT
		{
			auto transition = pEvil->CreateTransition(State::HIT);

			transition->AddCondition<EnemyCondition_isTakingDamage>(true);
		}
	}

	//KICK
	{
		Action<Enemy>* pKick = mpStateMachine->CreateAction<EnemyAction_Evil>(State::KICK);

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

void Enemy::Hit()
{
	std::cout << "Test" << std::endl;
	isTakingDamage = true;
}

void Enemy::Kick()
{
	isAttacking = true;
}

void Enemy::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();

	mState = (Enemy::State)mpStateMachine->GetCurrentState();
	const char* stateName = GetStateName(mState);
	Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);

	float dt = GetDeltaTime();
	mpStateMachine->Update();
	animEnemy->update(dt);
}

