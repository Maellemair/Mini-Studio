#pragma once
#include "PhysicalEntity.h"
#include <SFML/Graphics.hpp>

class Bullets : public PhysicalEntity
{
public:
	void OnCollision(Entity* collidedWith) override;
	void OnUpdate() override;

};

