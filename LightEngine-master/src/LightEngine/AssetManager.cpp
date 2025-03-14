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
	pathLevel.push_back("../../../res/Layout_Test.txt");
}

void Texture::Init()
{
	if (!textObject["Grass"].loadFromFile("../../../res/grass_texture.jpg")) {
		std::cout << "Erreur chargement grass_texture.jpg" << std::endl;
	}

	if (!textObject["Dirt"].loadFromFile("../../../res/dirt.jpg")) {
		std::cout << "Erreur chargement Dirt.jpg" << std::endl;
	}

	if (!textObject["Background"].loadFromFile("../../../res/tree_texture.png")) {
		std::cout << "Erreur chargement tree_texture.png" << std::endl;
	}
}