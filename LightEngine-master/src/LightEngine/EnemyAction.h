#pragma once
#include "Action.h"
#include "EnemyVolant.h"
#include "EnemyGround.h"

#include <iostream>

class EnemyGroundAction_Evil : public Action<EnemyGround>
{
public:
	void OnStart(EnemyGround* pEnemy) override { pEnemy->animEnemy->setAnimation("idleEvil"); }
	void OnUpdate(EnemyGround* pEnemy) override {}
	void OnEnd(EnemyGround* pEnemy) override {}
};

class EnemyGroundAction_Kick : public Action<EnemyGround>
{
	sf::Clock animTime;
public:
	void OnStart(EnemyGround* pEnemy) override { pEnemy->animEnemy->setAnimation("kick"); animTime.restart(); }
	void OnUpdate(EnemyGround* pEnemy) override;
	void OnEnd(EnemyGround* pEnemy) override {}
};

class EnemyGroundAction_Hit : public Action<EnemyGround>
{
	sf::Clock animTime;
public:
	void OnStart(EnemyGround* pEnemy) override { pEnemy->animEnemy->setAnimation("hit"); ; animTime.restart(); }
	void OnUpdate(EnemyGround* pEnemy) override;
	void OnEnd(EnemyGround* pEnemy) override {}
};

class EnemyGroundAction_Nice : public Action<EnemyGround>
{
public:
	void OnStart(EnemyGround* pEnemy) override { pEnemy->animEnemy->setAnimation("idleNice"); }
	void OnUpdate(EnemyGround* pEnemy) override {}
	void OnEnd(EnemyGround* pEnemy) override {}
};

class EnemyVolantAction_Evil : public Action<EnemyVolant>
{
public:
	void OnStart(EnemyVolant* pEnemy) override { pEnemy->animEnemy->setAnimation("idleEvil"); }
	void OnUpdate(EnemyVolant* pEnemy) override {}
	void OnEnd(EnemyVolant* pEnemy) override {}
};

class EnemyVolantAction_Shoot : public Action<EnemyVolant>
{
	sf::Clock animTime;
public:
	void OnStart(EnemyVolant* pEnemy) override { pEnemy->animEnemy->setAnimation("shoot"); animTime.restart(); }
	void OnUpdate(EnemyVolant* pEnemy) override;
	void OnEnd(EnemyVolant* pEnemy) override {}
};

class EnemyVolantAction_Hit : public Action<EnemyVolant>
{
	sf::Clock animTime;
public:
	void OnStart(EnemyVolant* pEnemy) override { pEnemy->animEnemy->setAnimation("hit"); ; animTime.restart(); }
	void OnUpdate(EnemyVolant* pEnemy) override;
	void OnEnd(EnemyVolant* pEnemy) override {}
};

class EnemyVolantAction_Nice : public Action<EnemyVolant>
{
public:
	void OnStart(EnemyVolant* pEnemy) override { pEnemy->animEnemy->setAnimation("idleNice"); }
	void OnUpdate(EnemyVolant* pEnemy) override {}
	void OnEnd(EnemyVolant* pEnemy) override {}
};

