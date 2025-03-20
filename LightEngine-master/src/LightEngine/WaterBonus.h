#pragma once
#include "Bonus.h"

class Texture;

class WaterBonus : public Bonus
{

public:
	void OnInitialize() override;
	void isCollid(Player* pPlayer) override;
};

