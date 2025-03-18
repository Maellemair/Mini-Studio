#pragma once

#include "Condition.h"
#include "Player.h"

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

class PlayerCondition_isFalling : public Condition<Player>
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

