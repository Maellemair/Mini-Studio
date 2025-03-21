#include "LifeBonus.h"
#include "AssetManager.h"
#include "Player.h"

void LifeBonus::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["item"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(9, 18)));
}

void LifeBonus::isCollid(Player* pPlayer)
{
	pPlayer->GiveHealth();
}
