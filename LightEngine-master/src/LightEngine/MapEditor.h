#pragma once
#include <fstream>
#include <iostream>
#include <istream>
#include <string>

#include "Scene.h"

class ObjectEntity;
class Enemy;
class GameManager;
class Bonus;

class MapEditor
{
	std::ifstream fichier;
	std::vector<ObjectEntity*> mPlateforms;
	std::vector<Enemy*> mEnemy;
	std::vector<Bonus*> mBonus;

public:
	void Load(const char* path);
	void CreateMap(float pResolution, std::map<char, ObjectEntity*> pMapObject);
	
	std::vector<ObjectEntity*> GetMap();
	std::vector<Enemy*> GetEnemy();
	std::vector<Bonus*> GetBonus();
};

