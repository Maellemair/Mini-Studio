#include "EnemyAction.h"

void EnemyGoundAction_Kick::OnUpdate(EnemyGround* pEnemy)
{
	std::cout << pEnemy->GetStateCollision() << std::endl;
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
}

void EnemyVolantAction_Hit::OnUpdate(EnemyVolant* pEnemy)
{
}
