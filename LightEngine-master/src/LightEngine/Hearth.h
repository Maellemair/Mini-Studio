#pragma once
#include "ObjectEntity.h"

class Texture;

class Hearth : public ObjectEntity
{
	bool isDead = false;
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void SetDead(bool pState) { isDead = pState; }
};

