#include "AssetManager.h"


Level* Level::instance = nullptr;
Texture* Texture::instance = nullptr;

Level::Level()
{
	Init();
}

Level* Level::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Level();
	}
	return instance;
}

Texture::Texture()
{
	Init();
}

Texture* Texture::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Texture();
	}
	return instance;
}

void Level::Init()
{
	pathLevel.push_back("../../../res/Layout_plateform_lv1.txt");
	pathLevel.push_back("../../../res/Layout_Rock_lv1.txt");
}

void Texture::Init()
{
	if (!textObject["TileGrass"].loadFromFile("../../../res/tilemap_grass.png")) {
		std::cout << "Erreur chargement grass_texture.jpg" << std::endl;
	}

	if (!textObject["Background"].loadFromFile("../../../res/tree_texture.png")) {
		std::cout << "Erreur chargement tree_texture.png" << std::endl;
	}

	if (!textObject["TileRocks"].loadFromFile("../../../res/tilemap_rocks.png")) {
		std::cout << "Erreur chargement tree_texture.png" << std::endl;
	}
}