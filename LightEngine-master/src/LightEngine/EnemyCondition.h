#pragma once
#include "Condition.h"
#include "Enemy.h"

class EnemyCondition_isTakingDamage : public Condition<Enemy>
{
public:
	bool OnTest(Enemy* owner) override;
};

class EnemyCondition_isAttacking : public Condition<Enemy>
{
public:
	bool OnTest(Enemy* owner) override;
};

