#include "Left_edge_dirt.h"
#include "AssetManager.h"

void Left_edge_dirt::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(112, 16), sf::Vector2i(16, 16)));
}

ObjectEntity* Left_edge_dirt::Clone(float height, float width, float posX, float posY)
{
	Left_edge_dirt* tempLeft_edge_dirt = CreateRectangle<Left_edge_dirt>(height, width, sf::Color::Green);
	tempLeft_edge_dirt->Create(posX, posY);
	return tempLeft_edge_dirt;
}
