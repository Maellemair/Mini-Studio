#pragma once
#include "Condition.h"
#include "Enemy.h"

class EnemyCondition_IsColliding : public Condition<Enemy>
{
public:
	bool OnTest(Enemy* owner) override;
};

