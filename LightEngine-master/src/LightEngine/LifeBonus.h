#pragma once
#include "Bonus.h"

class Player;
class Texture;

class LifeBonus : public Bonus
{

public:
	void OnInitialize() override;
	void isCollid(Player* pPlayer) override;
};

