#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

template<typename T>
class StateMachine;
class Texture;
class Sound;
class Bullets;
class Hearth;

class Player : public PhysicalEntity, public Animation
{
	enum State
	{
		WALK,
		JUMP,
		FALL,
		SHOOT,
		IDLE,
		DEATH,
		HIT,
		Count
	};

	int MaxLife = 3;
	int mLife = MaxLife;

	State mState;
	sf::Clock mClockDoubleJump;
	float jumpCooldown = 0.5f;
	Animation* animPlayer;
	StateMachine<Player>* mpStateMachine;
	Sound* mSoundJump;	
	Sound* mSoundHit;	
	Sound* mSoundShoot;	
	Sound* mSoundDeath;

	int lastDirection = 1;
	int mAmmoMax = 12;
	int mAmmo = mAmmoMax;

	bool isTakingDamage = false;
	bool isShooting = false;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetState(State pState);
	void SetGravity(bool state) { mGravity = state; }
	const char* GetStateName(State state) const;
	Entity* GetColliderEntity() override { return PhysicalEntity::GetColliderEntity(); }
	void GiveHealth() { mLife++; }
	void ReloadWater() { mAmmo = mAmmoMax; }
	int getLastDirection();
	void setLastDirection(int dir);
	void Move(int key);
	void Reset();
	void Jump();
	void Shoot();
	void TakeHit(float posX, int pLifeLost = 1);
	void Death() { SetDirection(0, 0); SetPosition(1280 / 2, ((720 / 4) * 3) + 3000); }
	int GetLife() { return mLife; }
	bool GetIsTakingDamage() { return isTakingDamage; }
	bool GetIsShooting() { return isShooting; }
	int GetAmmo() { return mAmmo; }
	void ResetAmmo() { mAmmo = mAmmoMax; }
	bool IsDead() { return mLife <= 0; }

	float invicibilityTime = 0.0f;
	float repulsionTimer = 0.0f;

protected:
	friend class PlayerAction_Fall;
	friend class PlayerAction_Shoot;
	friend class PlayerAction_Idle; 
	friend class PlayerAction_Jump;
	friend class PlayerAction_Walk;
	friend class PlayerAction_Hit;
	friend class PlayerAction_Death;
};

