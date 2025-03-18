#include "Right_edge_grass.h"
#include "../AssetManager.h"

void Right_edge_grass::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(16, 0), sf::Vector2i(16, 16)));
}

ObjectEntity* Right_edge_grass::Clone(float height, float width, float posX, float posY)
{
	Right_edge_grass* tempRight_edge_grass = CreateRectangle<Right_edge_grass>(height, width, sf::Color::Green);
	tempRight_edge_grass->Create(posX, posY);
	return tempRight_edge_grass;
}
