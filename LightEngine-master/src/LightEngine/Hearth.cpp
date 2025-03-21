#include "Hearth.h"
#include "AssetManager.h"

void Hearth::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["hud/eau"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 9), sf::Vector2i(9, 9)));
}

void Hearth::OnUpdate()
{
	if (isDead)
	{
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(9, 9), sf::Vector2i(9, 9)));
	}
	else
	{
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 9), sf::Vector2i(9, 9)));
	}
}
