#include "Enemy.h"
#include "AssetManager.h"
#include "StateMachine.h"
#include "EnemyCondition.h"
#include "EnemyAction.h"
#include "Debug.h"
#include "SampleScene.h"

void Enemy::OnInitialize()
{
	SetTag(15);
}

void Enemy::Hit()
{
	isTakingDamage = true;
}

void Enemy::OnUpdate()
{
	float dt = GetDeltaTime();
	animEnemy->update(dt);
}

