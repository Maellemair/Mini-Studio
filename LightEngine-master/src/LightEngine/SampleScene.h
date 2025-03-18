#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class ObjectEntity;
class Background;
class MapEditor;
class Music;

//assets
class Grass;
class Dirt;
class Right_edge_grass;
class Left_edge_grass;
class Left_edge_dirt;
class Right_edge_dirt;
class Plateform;
class Plateform_middle;
class Plateform_edge_right;
class Plateform_edge_left;
class Left_dirt_fall;
class Right_dirt_fall;
class Rocks;

class SampleScene : public Scene
{
	sf::View* cam;
	Player* pEntity1;
	MapEditor* map;
	MapEditor* mapRocks;
	Background* bg;
	Background* filtre;
	Background* filtreArbre;
	Background* arbreBack;
	Background* arbre;
	std::vector<ObjectEntity*> mPlateforms;
	Music* mMusic;

private:
	std::map<char, ObjectEntity*> mObjectType;
	sf::Sprite background;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


