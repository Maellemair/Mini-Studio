#pragma once
#include "../Entity.h"

class Texture;

class Background : public Entity
{

public:
	void Load(const char* backgroundName);
};

