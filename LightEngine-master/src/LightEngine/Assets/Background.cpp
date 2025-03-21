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

void Background::OnUpdate(float delta, float pCampPos)
{
    float bgWidth = mShape->getSize().x;

    if (GetPosition().x + bgWidth <= pCampPos)
    {
        SetPosition(GetPosition().x + bgWidth * 2, mPos.y);
    }
    else if (GetPosition().x >= pCampPos + bgWidth)
    {
        SetPosition(GetPosition().x - bgWidth * 2, mPos.y);
    }

    mShape->move(-delta * mSpeed, 0);
}
