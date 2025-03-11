#pragma once
#include "PhysicalEntity.h"

class Player : public PhysicalEntity
{
public:
	void Move(float deltaTime, int key);
	void Jump();
};

