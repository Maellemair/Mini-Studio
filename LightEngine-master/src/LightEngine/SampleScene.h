#pragma once

#include "Scene.h"
#include <vector>

class Player;
class ObjectEntity;
class MapEditor;
class Music;

class SampleScene : public Scene
{
	Player* pEntity1;
	MapEditor* map;
	std::vector<ObjectEntity*> mPlateforms;
	Music* mMusic;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


