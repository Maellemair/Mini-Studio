#include "PlayerAction.h"

void PlayerAction_Hit::OnStart(Player* pPlayer)
{
	pPlayer->animPlayer->setAnimation("hit");
	animTime.restart();
}

void PlayerAction_Hit::OnUpdate(Player* pPlayer)
{
	if (animTime.getElapsedTime().asSeconds() >= 0.2f)
	{
		pPlayer->isTakingDamage = false;
	}
}
