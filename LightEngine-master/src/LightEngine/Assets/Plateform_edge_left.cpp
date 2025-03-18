#include "Plateform_edge_left.h"
#include "AssetManager.h"

void Plateform_edge_left::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(16, 48), sf::Vector2i(16, 16)));
}

ObjectEntity* Plateform_edge_left::Clone(float height, float width, float posX, float posY)
{
	Plateform_edge_left* tempPlateform_edge_left = CreateRectangle<Plateform_edge_left>(height, width, sf::Color::Green);
	tempPlateform_edge_left->Create(posX, posY);
	return tempPlateform_edge_left;
}

