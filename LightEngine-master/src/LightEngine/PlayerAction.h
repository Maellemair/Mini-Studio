#pragma once
#include "Action.h"
#include "Player.h"

class PlayerAction_Idle : public Action<Player>
{
public:
	void OnStart(Player* pPlant) override {}
	void OnUpdate(Player* pPlant) override {}
	void OnEnd(Player* pPlant) override {}
};

class PlayerAction_Walk : public Action<Player>
{
public:
	void OnStart(Player* pPlant) override {}
	void OnUpdate(Player* pPlant) override {}
	void OnEnd(Player* pPlant) override {}
};

class PlayerAction_Jump : public Action<Player>
{
public:
	void OnStart(Player* pPlant) override {}
	void OnUpdate(Player* pPlant) override {}
	void OnEnd(Player* pPlant) override {}
};

class PlayerAction_Fall : public Action<Player>
{
public:
	void OnStart(Player* pPlant) override {}
	void OnUpdate(Player* pPlant) override {}
	void OnEnd(Player* pPlant) override {}
};

