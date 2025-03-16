#include "Grass.h"
#include "AssetManager.h"

void Grass::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(32, 0), sf::Vector2i( 16, 16 )));
}

ObjectEntity* Grass::Clone(float height, float width, float posX, float posY)
{
	Grass* tempGrass = CreateRectangle<Grass>(height, width, sf::Color::Green);
	tempGrass->Create(posX, posY);
	return tempGrass;
}
