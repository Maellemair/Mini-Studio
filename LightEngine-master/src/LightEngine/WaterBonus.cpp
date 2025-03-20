#include "WaterBonus.h"
#include "AssetManager.h"

void WaterBonus::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["item"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(9, 18)));
}
