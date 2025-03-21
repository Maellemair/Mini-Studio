#pragma once

#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Enemy;
class EnemyVolant;
class EnemyGround;
class ObjectEntity;
class Background;
class MapEditor;
class Music;
class Bonus;
class Bullets;
class BulletsEnemy;
class Hearth;
class Reservoir;

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
class DeathZone;

class SampleScene : public Scene
{
private:
	bool isMenuActive = true;
	sf::View* cam;
	Player* pEntity1;
	Enemy* pEnemy;
	std::vector<Bullets*> bulletsList;
	std::vector<BulletsEnemy*> bulletsEnemyList;
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
	std::vector<Enemy*> mEnemys;
	std::vector<Bonus*> mBonus;
	std::vector<Hearth*> mHearths;
	Music* mMusic;
	Reservoir* mReservoir;
	sf::Vector2f mCamPos;
	sf::Vector2f lastCameraPosition;
	std::map<char, ObjectEntity*> mObjectType;

public:
	void OnInitialize() override;
	void DisplayMenu();
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void OnDestroy() override;
};


