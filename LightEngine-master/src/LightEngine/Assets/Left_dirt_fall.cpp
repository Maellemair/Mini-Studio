#include "Left_dirt_fall.h"
#include "../AssetManager.h"

void Left_dirt_fall::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(48, 16), sf::Vector2i(16, 16)));
}

ObjectEntity* Left_dirt_fall::Clone(float height, float width, float posX, float posY)
{
	Left_dirt_fall* tempLeft_dirt_fall = CreateRectangle<Left_dirt_fall>(height, width, sf::Color::Green);
	tempLeft_dirt_fall->Create(posX, posY);
	return tempLeft_dirt_fall;
}