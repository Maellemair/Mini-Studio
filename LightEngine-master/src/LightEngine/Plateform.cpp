#include "Plateform.h"
#include "AssetManager.h"

void Plateform::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 16)));
}

ObjectEntity* Plateform::Clone(float height, float width, float posX, float posY)
{
	Plateform* tempPlateform = CreateRectangle<Plateform>(height, width, sf::Color::Green);
	tempPlateform->Create(posX, posY);
	return tempPlateform;
}