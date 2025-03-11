#pragma once

#include "Scene.h"

class PhysicalEntity;

class PlatformerScene : public Scene
{
	PhysicalEntity* pEntity1;

private:
	int mWidth;
	int mHeight;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnEvent(const sf::Event& event) override;

};