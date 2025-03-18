#include "Background.h"
#include "../AssetManager.h"

void Background::Load(const char* backgroundName, sf::Vector2i pSize, sf::Vector2i pPos)
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m[backgroundName], true);
	mShape->setTextureRect(sf::IntRect(pPos, pSize));
}
