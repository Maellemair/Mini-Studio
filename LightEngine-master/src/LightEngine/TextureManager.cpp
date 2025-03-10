#include "TextureManager.h"

MapPath* MapPath::instance = nullptr;
StaticTextures* StaticTextures::instance = nullptr;

MapPath::MapPath()
{
	Init();
}

StaticTextures::StaticTextures()
{
	Init();
}

MapPath* MapPath::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MapPath();
	}
	return instance;
}

StaticTextures* StaticTextures::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new StaticTextures();
	}
	return instance;
}

void MapPath::Init()
{
	// fichier txt level : slide 79
	//posBricks.push_back("../../../res/assets/Layout/Layout1.txt"); 
}

void StaticTextures::Init()
{
}

void StaticTextures::Load(const char* pPath, const char* pNameId)
{
	if (!textObject[pNameId].loadFromFile(pPath)) {
		std::cout << "Erreur chargement" + *pNameId << std::endl;
	}
}

