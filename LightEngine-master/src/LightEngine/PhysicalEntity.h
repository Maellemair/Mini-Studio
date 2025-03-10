#pragma once
#include "Entity.h"
#include <iostream>
class PhysicalEntity : public Entity
{
	bool mGravity = false;
	float mGravitySpeed = 0.f;

public:
	void Fall(float deltaTime);
	void Jump();
	void OnUpdate() override;
};

