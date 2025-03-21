#pragma once
#include "Action.h"
#include "Player.h"

#include <iostream>

class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override { pPlayer->animPlayer->setAnimation("idle"); }
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Walk : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override { pPlayer->animPlayer->setAnimation("walk"); }
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Jump : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override { pPlayer->animPlayer->setAnimation("jump"); }
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Fall : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override { pPlayer->animPlayer->setAnimation("fall"); }
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Death : public Action<Player>
{
public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override {}
	void OnEnd(Player* pPlayer) override {}
};

class PlayerAction_Hit: public Action<Player>
{
	sf::Clock animTime;
public:
	void OnStart(Player* pPlayer) override;
	void OnUpdate(Player* pPlayer) override;
	void OnEnd(Player* pPlayer) override {}
};

