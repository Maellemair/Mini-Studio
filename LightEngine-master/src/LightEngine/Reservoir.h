#pragma once
#include "ObjectEntity.h"

class Texture;

class Reservoir : public ObjectEntity
{
public:
	void OnInitialize() override;
	void OnUpdate() override;
	void UpdateText(int pNbrAmmo);
};

