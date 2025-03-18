#pragma once
#include "../ObjectEntity.h"

class Left_dirt_fall : public ObjectEntity
{
public:
	void Create(float posX, float posY);
	ObjectEntity* Clone(float height, float width, float posX, float posY) override;
};

