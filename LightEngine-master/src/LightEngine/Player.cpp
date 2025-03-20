#include "Player.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "PlayerCondition.h"
#include "PlayerAction.h"
#include "StateMachine.h"
#include "json.hpp"
#include "Debug.h"
#include "Sound.h"
#include <fstream>

int Player::getLastDirection()
{
	return lastDirection;
}

void Player::setLastDirection(int dir)
{
	lastDirection = dir;
}

void Player::OnInitialize()
{
	SetTag(16);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_Player"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));

	animPlayer = new Animation;
	animPlayer->loadAnimations(m["animation_Player"], "../../../res/Player.json", mShape);
	
	mpStateMachine = new StateMachine<Player>(this, State::Count);

	//IDLE
	{
		Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::IDLE);

		//-> WALKING
		{
			auto transition = pIdle->CreateTransition(State::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsMoving>(true);
			transition->AddCondition<PlayerCondition_isGround>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> JUMP
		{
			auto transition = pIdle->CreateTransition(State::JUMP);

			transition->AddCondition<PlayerCondition_isGround>(false);
			transition->AddCondition<PlayerCondition_isJumping>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> HIT
		{
			auto transition = pIdle->CreateTransition(State::HIT);

			transition->AddCondition<PlayerCondition_takeDamage>(true);
		}

		//-> DEATH
		{
			auto transition = pIdle->CreateTransition(State::DEATH);

			transition->AddCondition<PlayerCondition_isDead>(true);
		}
	}

	//FALL
	{
		Action<Player>* pFalling = mpStateMachine->CreateAction<PlayerAction_Fall>(State::FALL);

		//-> IDLE
		{
			auto transition = pFalling->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_isGround>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> JUMP
		{
			auto transition = pFalling->CreateTransition(State::JUMP);

			transition->AddCondition<PlayerCondition_isJumping>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> HIT
		{
			auto transition = pFalling->CreateTransition(State::HIT);

			transition->AddCondition<PlayerCondition_takeDamage>(true);
		}

		//-> DEATH
		{
			auto transition = pFalling->CreateTransition(State::DEATH);

			transition->AddCondition<PlayerCondition_isDead>(true);
		}
	}

	//WALK
	{
		Action<Player>* pWalking = mpStateMachine->CreateAction<PlayerAction_Walk>(State::WALK);

		//-> IDLE
		{
			auto transition = pWalking->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_IsMoving>(false);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> JUMP
		{
			auto transition = pWalking->CreateTransition(State::JUMP);

			transition->AddCondition<PlayerCondition_isGround>(false);
			transition->AddCondition<PlayerCondition_isJumping>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> FALL
		{
			auto transition = pWalking->CreateTransition(State::FALL);

			transition->AddCondition<PlayerCondition_isGround>(false);
			transition->AddCondition<PlayerCondition_isFalling>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> HIT
		{
			auto transition = pWalking->CreateTransition(State::HIT);

			transition->AddCondition<PlayerCondition_takeDamage>(true);
		}

		//-> DEATH
		{
			auto transition = pWalking->CreateTransition(State::DEATH);

			transition->AddCondition<PlayerCondition_isDead>(true);
		}
	}

	//JUMP
	{
		Action<Player>* pJumping = mpStateMachine->CreateAction<PlayerAction_Jump>(State::JUMP); 

		//-> FALL
		{
			auto transition = pJumping->CreateTransition(State::FALL);

			transition->AddCondition<PlayerCondition_isFalling>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}
		
		//-> IDLE
		{
			auto transition = pJumping->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_isFalling>(false);
			transition->AddCondition<PlayerCondition_isGround>(true);
			transition->AddCondition<PlayerCondition_takeDamage>(false);
		}

		//-> HIT
		{
			auto transition = pJumping->CreateTransition(State::HIT);

			transition->AddCondition<PlayerCondition_takeDamage>(true);
		}

		//-> DEATH
		{
			auto transition = pJumping->CreateTransition(State::DEATH);

			transition->AddCondition<PlayerCondition_isDead>(true);
		}
	}

	//Death
	{
		Action<Player>* pDeath = mpStateMachine->CreateAction<PlayerAction_Death>(State::DEATH);
	}

	//Hit
	{
		Action<Player>* pHit = mpStateMachine->CreateAction<PlayerAction_Hit>(State::HIT);

		//-> Death
		{
			auto transition = pHit->CreateTransition(State::DEATH);

			transition->AddCondition<PlayerCondition_isDead>(true);
			transition->AddCondition<PlayerCondition_animHitFinish>(true);
		}

		//-> Idle
		{
			auto transition = pHit->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_isGround>(true);
			transition->AddCondition<PlayerCondition_isFalling>(false);
			transition->AddCondition<PlayerCondition_animHitFinish>(true);
		}

		//-> Fall
		{
			auto transition = pHit->CreateTransition(State::FALL);

			transition->AddCondition<PlayerCondition_isFalling>(true);
			transition->AddCondition<PlayerCondition_isGround>(false);
			transition->AddCondition<PlayerCondition_animHitFinish>(true);
		}
	}

	mpStateMachine->SetState(State::JUMP);
	mState = (Player::State)mpStateMachine->GetCurrentState();
	mSound = new Sound();	
}

void Player::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	mState = (Player::State)mpStateMachine->GetCurrentState();
	const char* stateName = GetStateName(mState);

	float dt = GetDeltaTime();
	Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);
	mpStateMachine->Update();
	animPlayer->update(dt);
	PhysicalEntity::OnUpdate();
}

void Player::SetState(State pState)
{
	mState = pState;
}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case IDLE: return "Idle";
	case FALL: return "Fall";
	case WALK: return "Walk";
	case JUMP: return "Jump";
	case DEATH: return "Death";
	case HIT: return "Hit";
	default: return "Unknown";
	}
}

void Player::Move(int key)
{
	if (key == -1)
	{
		animPlayer->SetIsFacingRight(false);
	}
	else if(key == 1)
	{
		animPlayer->SetIsFacingRight(true);
	}
	SetDirection(key, 0, 250);
}

void Player::Reset()
{
	sf::Vector2f pPosCenter = sf::Vector2f(GameManager::Get()->GetScene()->GetWindowWidth(),
		GameManager::Get()->GetScene()->GetWindowHeight());
	SetPosition(pPosCenter.x / 2, pPosCenter.y / 4);
	SetCollider(pPosCenter.x / 2, pPosCenter.y / 4, mBoxCollider->ySize, mBoxCollider->xSize);
	mLife = 3;
	mpStateMachine->SetState(IDLE);
	mGravitySpeed = 0;
}

void Player::Jump()
{
	if (mNbrJump >= 2 || mClockDoubleJump.getElapsedTime().asSeconds() < jumpCooldown)
		return;

	ColliderEntity = nullptr;
	state = None;
	sf::Vector2f pPos = GetPosition(0.5f, 0.5f);
	SetPosition(pPos.x, pPos.y - 1);
	SetCollider(pPos.x, pPos.y - 1, mBoxCollider->ySize, mBoxCollider->xSize);
	mGravity = true;
	mGravitySpeed = -350;
	mNbrJump++;
	mClockDoubleJump.restart();

	mSound->Load("../../../res/jump_sound.wav");
	mSound->Play();
}

void Player::TakeHit()
{
	animHitTime.restart();
	mLife--;
	isTakingDamage = true;
	if (mLife <= 0)
	{
		//GameOver
	}
}

void Player::Dash(float deltaTime)
{
	SetDirection(lastDirection, 0, 800);
}





