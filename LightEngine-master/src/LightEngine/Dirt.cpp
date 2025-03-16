#include "Dirt.h"
#include "AssetManager.h"

void Dirt::Create(float posX, float posY)
{
	SetTag(3);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(32, 16), sf::Vector2i(16, 16)));
}

ObjectEntity* Dirt::Clone(float height, float width, float posX, float posY)
{
	Dirt* tempGrass = CreateRectangle<Dirt>(height, width, sf::Color::Cyan);
	tempGrass->Create(posX, posY);
	return tempGrass;
}
