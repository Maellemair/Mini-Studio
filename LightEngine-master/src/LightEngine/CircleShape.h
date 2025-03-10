#pragma once
#include "Entity.h"

class CircleShape : Entity
{
	sf::CircleShape mShape;

	float radius;

public:
	void SetPosition(float x, float y, float ratioX, float ratioY) override;
	float GetRadius() const override { return radius; }
};

