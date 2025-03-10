#pragma once

#include "Scene.h"

class DummyEntity;

class SceneGame : public Scene
{
	DummyEntity* pPlayer;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

