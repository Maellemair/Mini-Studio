#pragma once
#include "PhysicalEntity.h"
#include "Animation.h"

class Texture;

class BulletsEnemy : public PhysicalEntity, public Animation
{
	Animation* animBullets;
public:
	void OnInitialize() override;
	void OnUpdate() override;
};