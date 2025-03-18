#pragma once
#include "../Entity.h"

class Texture;

class Background : public Entity
{

public:
	void Load(const char* backgroundName, sf::Vector2i pSize, sf::Vector2i pPos);
};

