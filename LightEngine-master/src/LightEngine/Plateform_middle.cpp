#include "Plateform_middle.h"
#include "AssetManager.h"

void Plateform_middle::Create(float posX, float posY)
{
	SetTag(2);
	SetPosition(posX, posY);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["TileGrass"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(32, 48), sf::Vector2i(16, 16)));
}

ObjectEntity* Plateform_middle::Clone(float height, float width, float posX, float posY)
{
	Plateform_middle* tempPlateform_middle = CreateRectangle<Plateform_middle>(height, width, sf::Color::Green);
	tempPlateform_middle->Create(posX, posY);
	return tempPlateform_middle;
}