#pragma once

#include "Scene.h"
#include <vector>

class Player;
class Enemy;
class ObjectEntity;
class MapEditor;
class Bullets;

class SampleScene : public Scene
{
	Player* pEntity1;
	Enemy* pEnemy;
	std::vector<Bullets*> bulletsList;
	MapEditor* map;
	std::vector<ObjectEntity*> mPlateforms;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


