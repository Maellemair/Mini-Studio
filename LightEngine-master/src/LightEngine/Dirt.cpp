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
	mShape->setTexture(&m["Dirt"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(512, 512)));
}

ObjectEntity* Dirt::Clone(float height, float width, float posX, float posY)
{
	Dirt* tempGrass = CreateRectangle<Dirt>(height, width, sf::Color::Cyan);
	tempGrass->Create(posX, posY);
	return tempGrass;
}
