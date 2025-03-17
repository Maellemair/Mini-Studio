#include "Right_edge_dirt.h"
#include "AssetManager.h"

void Right_edge_dirt::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(128, 16), sf::Vector2i(16, 16)));
}

ObjectEntity* Right_edge_dirt::Clone(float height, float width, float posX, float posY)
{
	Right_edge_dirt* tempRight_edge_dirt = CreateRectangle<Right_edge_dirt>(height, width, sf::Color::Green);
	tempRight_edge_dirt->Create(posX, posY);
	return tempRight_edge_dirt;
}
