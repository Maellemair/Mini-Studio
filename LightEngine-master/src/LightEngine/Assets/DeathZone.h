#pragma once
#include "../ObjectEntity.h"

class DeathZone : public ObjectEntity
{
public:
	void Create(float posX, float posY);
	ObjectEntity* Clone(float height, float width, float posX, float posY);
};

