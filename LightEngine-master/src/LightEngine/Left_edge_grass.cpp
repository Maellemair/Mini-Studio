#include "Left_edge_grass.h"
#include "AssetManager.h"

void Left_edge_grass::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(48, 0), sf::Vector2i(16, 16)));
}

ObjectEntity* Left_edge_grass::Clone(float height, float width, float posX, float posY)
{
	Left_edge_grass* tempLeft_edge_grass = CreateRectangle<Left_edge_grass>(height, width, sf::Color::Green);
	tempLeft_edge_grass->Create(posX, posY);
	return tempLeft_edge_grass;
}
