#pragma once

#include "Scene.h"

class Player;

class SceneGame : public Scene
{
	Player* pPlayer;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};

