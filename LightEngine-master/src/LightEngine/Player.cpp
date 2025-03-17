#include "Player.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "PlayerCondition.h"
#include "PlayerAction.h"
#include "json.hpp"
#include "Debug.h"
#include <fstream>

void Player::OnInitialize()
{
	SetTag(16);
	mpStateMachine = new StateMachine<Player>(this, State::Count);

	//IDLE
	{
		Action<Player>* pIdle = mpStateMachine->CreateAction<PlayerAction_Idle>(State::IDLE);

		//-> WALKING
		{
			auto transition = pIdle->CreateTransition(State::WALK);

			auto condition = transition->AddCondition<PlayerCondition_IsMoving>(true);
		}

		//-> JUMP
		{
			auto transition = pIdle->CreateTransition(State::JUMP);

			transition->AddCondition<PlayerCondition_isGround>(true);
		}
	}

	//FALL
	{
		Action<Player>* pFalling = mpStateMachine->CreateAction<PlayerAction_Fall>(State::FALL);

		//-> IDLE
		{
			auto transition = pFalling->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_isGround>(true);
		}
	}

	//WALK
	{
		Action<Player>* pWalking = mpStateMachine->CreateAction<PlayerAction_Walk>(State::WALK);

		//-> IDLE
		{
			auto transition = pWalking->CreateTransition(State::IDLE);

			transition->AddCondition<PlayerCondition_IsMoving>(false);
		}

		//-> JUMP
		{
			auto transition = pWalking->CreateTransition(State::JUMP);

			transition->AddCondition<PlayerCondition_isGround>(true);
		}
		
		//-> FALL
		{
			auto transition = pWalking->CreateTransition(State::FALL);

			transition->AddCondition<PlayerCondition_isGround>(false);
			transition->AddCondition<PlayerCondition_isFalling>(true);
		}
	}

	//JUMP
	{
		Action<Player>* pJumping = mpStateMachine->CreateAction<PlayerAction_Jump>(State::JUMP);

		//-> FALL
		{
			auto transition = pJumping->CreateTransition(State::FALL);

			transition->AddCondition<PlayerCondition_isFalling>(true);
		}
	}

	mpStateMachine->SetState(State::FALL);

	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_Player"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
	
	animIdle = new Animation();
	animJump = new Animation();
	
	std::ifstream fichier("../../../res/Player.json");
	if (fichier.is_open())
	{
		nlohmann::json data;
		fichier >> data;
		fichier.close();

		animIdle->SetShape(mShape, sf::Vector2f(0, 0), data["animations"]["idle"]["frames"], 
			data["animations"]["idle"]["timeProgress"], data["animations"]["idle"]["loop"]);
		animJump->SetShape(mShape, sf::Vector2f(0, 32), data["animations"]["jump"]["frames"], 
			data["animations"]["jump"]["timeProgress"], data["animations"]["jump"]["loop"]);
	}
	else
	{
		std::cout << "le fichier d'animation n'existe pas !" << std::endl;
		return;
	}
}

const char* Player::GetStateName(State state) const
{
	switch (state)
	{
	case IDLE: return "Idle";
	case FALL: return "Fall";
	case WALK: return "Walk";
	case JUMP: return "Jump";
	default: return "Unknown";
	}
}

void Player::OnUpdate()
{
	const sf::Vector2f& position = GetPosition();
	const char* stateName = GetStateName((Player::State)mpStateMachine->GetCurrentState());

	float dt = GetDeltaTime();
	if (mState == IDLE)
	{
		animIdle->Update(dt);
	}
	else if (mState == JUMP)
	{
		animIdle->Update(dt);
	}
	else if (mState == WALK)
	{
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
		animJump->ResetNBrLoop();
	}
	else if (mState == FALL)
	{
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
		animJump->ResetNBrLoop();
	}

	Debug::DrawText(position.x, position.y - 50, stateName, 0.5f, 0.5f, sf::Color::White);
	mpStateMachine->Update();
	PhysicalEntity::OnUpdate();
}

void Player::SetState(State pState)
{
	mState = pState;
}

void Player::Move(int key)
{
	SetDirection(key, 0, 250);
}

void Player::Reset()
{
	sf::Vector2f pPosCenter = sf::Vector2f(GameManager::Get()->GetScene()->GetWindowWidth(),
		GameManager::Get()->GetScene()->GetWindowHeight());
	SetPosition(pPosCenter.x / 2, pPosCenter.y / 4);
	SetCollider(pPosCenter.x / 2, pPosCenter.y / 4, mBoxCollider->ySize, mBoxCollider->xSize);
	mGravitySpeed = 0;
}

void Player::Jump()
{
	if (GetState() == TOP || mNbrJump >= 2 || mClockDoubleJump.getElapsedTime().asSeconds() < jumpCooldown)
		return;

	sf::Vector2f pPos = GetPosition(0.5f, 0.5f);
	SetPosition(pPos.x, pPos.y - 1);
	SetCollider(pPos.x, pPos.y - 1, mBoxCollider->ySize, mBoxCollider->xSize);
	mGravity = true;
	mGravitySpeed = -350;
	mNbrJump++;
	mClockDoubleJump.restart();
}
