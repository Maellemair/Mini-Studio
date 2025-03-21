#pragma once
#include "../Entity.h"

class Texture;

class Background : public Entity
{
	float mSpeed;
	sf::Vector2f mPos;

public:
	void Load(const char* backgroundName, sf::Vector2i pSize, sf::Vector2i pPos, float speed, sf::Vector2f pPosShape);
	void OnUpdate(float delta, float pCampPos);
};

