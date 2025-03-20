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
		std::cout << "Erreur chargement tilemap_grass.jpg" << std::endl;
	}

	if (!textObject["Background"].loadFromFile("../../../res/sunshine_background.png")) {
		std::cout << "Erreur chargement sunshine_background.png" << std::endl;
	}

	if (!textObject["TileRocks"].loadFromFile("../../../res/tilemap_rocks.png")) {
		std::cout << "Erreur chargement tilemap_rocks.png" << std::endl;
	}

	if (!textObject["animation_Player"].loadFromFile("../../../res/sprite_sheet_bot.png")) {
		std::cout << "Erreur chargement sprite_sheet_bot.png" << std::endl;
	}

	if (!textObject["animation_EnnemySol"].loadFromFile("../../../res/sunshine_plante_sol.png")) {
		std::cout << "Erreur chargement sprite_sheet_bot.png" << std::endl;
	}

	if (!textObject["animation_EnnemyVolant"].loadFromFile("../../../res/sunshine_plante_volante.png")) {
		std::cout << "Erreur chargement sprite_sheet_bot.png" << std::endl;
	}

	if (!textObject["filtre"].loadFromFile("../../../res/sunshine_atmosphere.png")) {
		std::cout << "Erreur chargement sunshine_atmosphere.png" << std::endl;
	}

	if (!textObject["Tree"].loadFromFile("../../../res/sunshine_tree.png")) {
		std::cout << "Erreur chargement sunshine_tre.png" << std::endl;
	}

	if (!textObject["item"].loadFromFile("../../../res/sunshine_item.png")) {
		std::cout << "Erreur chargement sunshine_tre.png" << std::endl;
	}

	if (!textObject["hud/eau"].loadFromFile("../../../res/sunshine_9x9.png")) {
		std::cout << "Erreur chargement sunshine_tre.png" << std::endl;
	}

	if (!textObject["uiReservoir"].loadFromFile("../../../res/sunshine_ui_reservoir_deau.png")) {
		std::cout << "Erreur chargement sunshine_tre.png" << std::endl;
	}
}