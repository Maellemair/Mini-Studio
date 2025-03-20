#pragma once

#include "Condition.h"
#include "Player.h"

class Enemy;

class PlayerCondition_IsMoving : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_isGround : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_isJumping : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_isFalling : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_isDead : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

class PlayerCondition_takeDamage : public Condition<Player>
{
public:
	bool OnTest(Player* owner) override;
};

//class PlayerCondition_ : public Condition<Player>
//{
//public:
//	bool OnTest(Player* owner) override;
//};
//
//class PlayerCondition : public Condition<Player>
//{
//public:
//	bool OnTest(Player* owner) override;
//};

