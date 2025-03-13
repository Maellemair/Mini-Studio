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
	std::vector<ObjectEntity*> mObjects;

public:
	void Load(const char* path);
	void CreateMap(float pResolution);
	std::vector<ObjectEntity*> GetMap();
};

