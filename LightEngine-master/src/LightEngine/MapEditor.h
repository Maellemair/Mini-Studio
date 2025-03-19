#pragma once
#include <fstream>
#include <iostream>
#include <istream>
#include <string>

#include "Scene.h"

class ObjectEntity;
class GameManager;

class MapEditor
{
	std::ifstream fichier;
	std::vector<ObjectEntity*> mPlateforms;
	//std::vector<ObjectEntity*> mEnemy;

public:
	void Load(const char* path);
	void CreateMap(float pResolution, std::map<char, ObjectEntity*> pMapObject);
	
	std::vector<ObjectEntity*> GetMap();
};

