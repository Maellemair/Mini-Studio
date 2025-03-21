#pragma once
#include "Condition.h"
#include "EnemyVolant.h"
#include "EnemyGround.h"

class EnemyVolantCondition_isTakingDamage : public Condition<EnemyVolant>
{
public:
	bool OnTest(EnemyVolant* owner) override;
};

class EnemyVolantCondition_isAttacking : public Condition<EnemyVolant>
{
public:
	bool OnTest(EnemyVolant* owner) override;
};

class EnemyGroundCondition_isTakingDamage : public Condition<EnemyGround>
{
public:
	bool OnTest(EnemyGround* owner) override;
};

class EnemyGroundCondition_isAttacking : public Condition<EnemyGround>
{
public:
	bool OnTest(EnemyGround* owner) override;
};

class EnemyVolantCondition_isDead : public Condition<EnemyVolant>
{
public:
	bool OnTest(EnemyVolant* owner) override;
};

class EnemyGroundCondition_isDead : public Condition<EnemyGround>
{
public:
	bool OnTest(EnemyGround* owner) override;
};

