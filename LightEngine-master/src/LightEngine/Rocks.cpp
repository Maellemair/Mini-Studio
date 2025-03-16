#include "Rocks.h"
#include "AssetManager.h"

void Rocks::Create(float posX, float posY)
{
	SetTag(1);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileRocks"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(48, 32)));
}

ObjectEntity* Rocks::Clone(float height, float width, float posX, float posY)
{
	Rocks* tempRocks = CreateRectangle<Rocks>(height, width, sf::Color::Green);
	tempRocks->Create(posX, posY);
	return tempRocks;
}