#pragma once
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class MapPath
{
	static MapPath* instance;

public:
	std::vector < std::string > posBricks;
	MapPath();
	static MapPath* GetInstance();
	void Init();
};

class StaticTextures
{
	static StaticTextures* instance;

public:

	std::map < std::string, sf::Texture > textObject;

	sf::Font textFont;

	StaticTextures();
	static StaticTextures* GetInstance();
	void Init();
	void Load(const char* pPath, const char* pNameId);
};