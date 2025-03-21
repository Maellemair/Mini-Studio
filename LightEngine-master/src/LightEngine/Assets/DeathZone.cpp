#include "DeathZone.h"

void DeathZone::Create(float posX, float posY)
{
	SetTag(3);
	SetPosition(posX, posY);
	SetRigidBody(true);
	sf::Vector2f pSize = sf::Vector2f(GetWidth(), GetHeight());
	SetCollider(posX, posY, pSize.y, pSize.x);
}

ObjectEntity* DeathZone::Clone(float height, float width, float posX, float posY)
{
	DeathZone* tempDeathZone = CreateRectangle<DeathZone>(height, width, sf::Color::Cyan);
	tempDeathZone->Create(posX, posY);
	return tempDeathZone;
}