#include "Sky.h"

void Sky::Create(float posX, float posY)
{
	SetTag(1);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
	mShape->setFillColor(sf::Color(0, 0, 0, 0));
}

ObjectEntity* Sky::Clone(float height, float width, float posX, float posY)
{
	Sky* tempGrass = CreateRectangle<Sky>(height, width, sf::Color::Cyan);
	tempGrass->Create(posX, posY);
	return tempGrass;
}