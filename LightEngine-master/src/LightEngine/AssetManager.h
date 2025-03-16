#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Level
{
	static Level* instance;

public:
	std::vector < std::string > pathLevel;

	Level();
	static Level* GetInstance();
	void Init();
};

class Texture
{
	static Texture* instance;

public:
	std::map < std::string, sf::Texture > textObject;
	sf::Texture TileGrass;
	sf::Texture TileRocks;
	sf::Texture Background;

	sf::Font textFont;

	Texture();
	static Texture* GetInstance();
	void Init();
};
