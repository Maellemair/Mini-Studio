#include "EnemyAction.h"

void EnemyGroundAction_Kick::OnUpdate(EnemyGround* pEnemy)
{
	if (animTime.getElapsedTime().asSeconds() >= 0.5f)
		pEnemy->isAttacking = false;
}

void EnemyGroundAction_Hit::OnUpdate(EnemyGround* pEnemy)
{
	if (animTime.getElapsedTime().asSeconds() >= 0.2f)
		pEnemy->isTakingDamage = false;
}

void EnemyVolantAction_Shoot::OnUpdate(EnemyVolant* pEnemy)
{
	if (animTime.getElapsedTime().asSeconds() >= 1.f)
		pEnemy->isAttacking = false;
}

void EnemyVolantAction_Hit::OnUpdate(EnemyVolant* pEnemy)
{
	if (animTime.getElapsedTime().asSeconds() >= 0.2f)
		pEnemy->isTakingDamage = false; 
}
