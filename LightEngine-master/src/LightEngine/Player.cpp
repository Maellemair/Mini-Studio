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

	//State
	{
		//IDLE
		{
			Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::IDLE);

			//-> WALKING
			{
				auto transition = pIdle->CreateTransition(State::WALK);

				transition->AddCondition<PlayerCondition_IsMoving>(true);
				transition->AddCondition<PlayerCondition_isGround>(true);
				transition->AddCondition<PlayerCondition_takeDamage>(false);
			}

			//-> Shoot
			{
				auto transition = pIdle->CreateTransition(State::SHOOT);

				transition->AddCondition<PlayerCondition_isShooting>(true);
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

				transition->AddCondition<PlayerCondition_isShooting>(false);
			}

			//-> Shoot
			{
				auto transition = pFalling->CreateTransition(State::SHOOT);

				transition->AddCondition<PlayerCondition_isShooting>(true);
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

		//Shoot
		{
			Action<Player>* pShooting = mpStateMachine->CreateAction<PlayerAction_Shoot>(State::SHOOT);

			//-> IDLE
			{
				auto transition = pShooting->CreateTransition(State::IDLE);

				transition->AddCondition<PlayerCondition_isGround>(true);
				transition->AddCondition<PlayerCondition_isShooting>(false);
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

			//-> Shoot
			{
				auto transition = pWalking->CreateTransition(State::SHOOT);

				transition->AddCondition<PlayerCondition_isShooting>(true);
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

			//-> Shoot
			{
				auto transition = pJumping->CreateTransition(State::SHOOT);

				transition->AddCondition<PlayerCondition_isShooting>(true);
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
				transition->AddCondition<PlayerCondition_takeDamage>(false);
			}

			//-> Idle
			{
				auto transition = pHit->CreateTransition(State::IDLE);

				transition->AddCondition<PlayerCondition_isGround>(true);
				transition->AddCondition<PlayerCondition_isFalling>(false);
				transition->AddCondition<PlayerCondition_takeDamage>(false);
			}

			//-> Fall
			{
				auto transition = pHit->CreateTransition(State::FALL);

				transition->AddCondition<PlayerCondition_isFalling>(true);
				transition->AddCondition<PlayerCondition_isGround>(false);
				transition->AddCondition<PlayerCondition_takeDamage>(false);
			}
		}
	}

	mpStateMachine->SetState(State::JUMP);
	mState = (Player::State)mpStateMachine->GetCurrentState();

	mSoundJump = new Sound();	
	mSoundShoot = new Sound();
	mSoundDeath = new Sound();
	mSoundHit = new Sound(); 

	mSoundJump->Load("../../../res/jumping_sound.wav");
	mSoundShoot->Load("../../../res/shooting_sound.wav");
	mSoundDeath->Load("../../../res/death_sound.wav");
	mSoundHit->Load("../../../res/damaged_sound.wav");
}

void Player::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	mState = (Player::State)mpStateMachine->GetCurrentState();
	const char* stateName = GetStateName(mState);

	if(isTakingDamage)
	{
		repulsionTimer -= GetDeltaTime();
		if (repulsionTimer <= 0.0f)
		{
			Move(0);
		}
	}
	float dt = GetDeltaTime();

	/*Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);*/

	animPlayer->update(dt);
	mpStateMachine->Update();
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
	case SHOOT: return "Shoot";
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

	mSoundJump->Play();
}

void Player::Shoot()
{
	isShooting = true;
}

void Player::TakeHit(float posX)
{
	mLife--;
	isTakingDamage = true;
	invicibilityTime = 0.0f;
	mSoundHit->Play();

	sf::Vector2f repulsionForce;
	if (GetPosition().x < posX)
	{
		repulsionForce = sf::Vector2f(-1.f, -1.f);
	}
	else
	{
		repulsionForce = sf::Vector2f(1, -1.f);
	}
	SetDirection(repulsionForce.x, repulsionForce.y, 500.f);
	repulsionTimer = 0.2f;
}

void Player::Dash(float deltaTime)
{
	SetDirection(lastDirection, 0, 800);
}





