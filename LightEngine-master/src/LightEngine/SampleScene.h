#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Enemy;
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
class Bullets;
class Bonus;

class SampleScene : public Scene
{
private:
	sf::View* cam;
	Player* pEntity1;
	Enemy* pEnemy;
	Bonus* pBonus;
	std::vector<Bullets*> bulletsList;
	MapEditor* map;
	MapEditor* mapRocks;
	Background* bg;
	Background* bg2;
	Background* filtre;
	Background* filtre2;
	Background* filtreArbre;
	Background* filtreArbre2;
	Background* arbreBack;
	Background* arbreBack2;
	Background* arbre;
	Background* arbre2;
	std::vector<Background*> mBackgrounds;
	std::vector<ObjectEntity*> mPlateforms;
	Music* mMusic;
	sf::Vector2f mCamPos;
	sf::Vector2f lastCameraPosition;
	std::map<char, ObjectEntity*> mObjectType;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
};


