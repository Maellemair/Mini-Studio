#include "Background.h"
#include "../AssetManager.h"

void Background::Load(const char* backgroundName, sf::Vector2i pSize, sf::Vector2i pPos, float pSpeed, sf::Vector2f pPosShape)
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m[backgroundName], true);
	mShape->setTextureRect(sf::IntRect(pPos, pSize));
	mPos = pPosShape;
	mSpeed = pSpeed;
}

void Background::OnUpdate(float delta)
{
 	if (GetPosition(0.5, 0.5).x <= mPos.x - mShape->getSize().x)
	{
		SetPosition(mPos.x + mShape->getSize().x, mPos.y);
	}
	mShape->move(-delta * mSpeed, 0);
}
