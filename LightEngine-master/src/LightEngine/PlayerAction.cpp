#include "PlayerAction.h"

void PlayerAction_Hit::OnStart(Player* pPlayer)
{
	pPlayer->animPlayer->setAnimation("hit");
	animTime.restart();

	pPlayer->MakeSound("../../../res/damaged_sound.wav", 1.0f);
}

void PlayerAction_Hit::OnUpdate(Player* pPlayer)
{
	if (animTime.getElapsedTime().asSeconds() >= 1.f)
		pPlayer->isTakingDamage = false;
}

void PlayerAction_Death::OnStart(Player* pPlayer)
{
	pPlayer->animPlayer->setAnimation("death");
	pPlayer->MakeSound("../../../res/death_sound.wav", 1.0f);
}