#include "Right_dirt_fall.h"
#include "../AssetManager.h"

void Right_dirt_fall::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(16, 16), sf::Vector2i(16, 16)));
}

ObjectEntity* Right_dirt_fall::Clone(float height, float width, float posX, float posY)
{
	Right_dirt_fall* tempRight_edge_grass = CreateRectangle<Right_dirt_fall>(height, width, sf::Color::Green);
	tempRight_edge_grass->Create(posX, posY);
	return tempRight_edge_grass;
}