#pragma once
#include "Action.h"
#include "Enemy.h"

#include <iostream>

class EnemyAction_Evil : public Action<Enemy>
{
public:
	void OnStart(Enemy* pEnemy) override { pEnemy->animEnemy->setAnimation("idleEvil"); }
	void OnUpdate(Enemy* pEnemy) override {}
	void OnEnd(Enemy* pEnemy) override {}
};

class EnemyAction_Kick : public Action<Enemy>
{
public:
	void OnStart(Enemy* pEnemy) override { pEnemy->animEnemy->setAnimation("kick"); }
	void OnUpdate(Enemy* pEnemy) override {}
	void OnEnd(Enemy* pEnemy) override {}
};

class EnemyAction_Hit : public Action<Enemy>
{
public:
	void OnStart(Enemy* pEnemy) override { pEnemy->animEnemy->setAnimation("hit"); }
	void OnUpdate(Enemy* pEnemy) override {}
	void OnEnd(Enemy* pEnemy) override {}
};

class EnemyAction_Nice : public Action<Enemy>
{
public:
	void OnStart(Enemy* pEnemy) override { pEnemy->animEnemy->setAnimation("idleNice"); }
	void OnUpdate(Enemy* pEnemy) override {}
	void OnEnd(Enemy* pEnemy) override {}
};

