#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class ObjectEntity;
class Background;
class MapEditor;
class Grass;
class Sky;
class Dirt;

class SampleScene : public Scene
{
	Player* pEntity1;
	MapEditor* map;
	Background* bg;
	std::vector<ObjectEntity*> mPlateforms;
	std::map<char, ObjectEntity*> mObjectType;
	sf::Sprite background;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


