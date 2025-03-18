#include "Background.h"
#include "../AssetManager.h"

void Background::Load(const char* backgroundName)
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m[backgroundName], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 720)));
}
