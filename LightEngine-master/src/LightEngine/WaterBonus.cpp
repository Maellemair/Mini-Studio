#include "WaterBonus.h"
#include "AssetManager.h"
#include "Player.h"

void WaterBonus::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["item"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(9, 0), sf::Vector2i(9, 18)));
}

void WaterBonus::isCollid(Player* pPlayer)
{
	pPlayer->ReloadWater();
}
