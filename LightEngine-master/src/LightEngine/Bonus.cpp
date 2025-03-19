#include "Bonus.h"
#include "AssetManager.h"

void Bonus::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_Player"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
}

void Bonus::OnCollision(Entity* collidedWith)
{
}

void Bonus::OnUpdate()
{

}
