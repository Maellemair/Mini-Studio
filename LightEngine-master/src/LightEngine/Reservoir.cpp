#include "Reservoir.h"
#include "AssetManager.h"

void Reservoir::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["uiReservoir"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(17, 29)));
}

void Reservoir::OnUpdate()
{
}

void Reservoir::UpdateText(int pNbrAmmo)
{
	int taille = pNbrAmmo / 2;
	switch (taille)
	{
	case 0:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(85, 0), sf::Vector2i(17, 29)));
		break;
	case 1:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(68, 0), sf::Vector2i(17, 29)));
		break;
	case 2:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(51, 0), sf::Vector2i(17, 29)));
		break;
	case 3:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(34, 0), sf::Vector2i(17, 29)));
		break;
	case 4:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(17, 0), sf::Vector2i(17, 29)));
		break;
	default:
		mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(17, 29)));
		break;
	}
}
