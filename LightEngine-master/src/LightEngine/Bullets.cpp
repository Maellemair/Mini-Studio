#include "Bullets.h"
#include "Enemy.h"
#include "AssetManager.h"

void Bullets::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["hud/eau"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(9, 9)));
}

void Bullets::OnCollision(Entity* collideWith)
{

}

void Bullets::Update()
{
	mGravitySpeed = -70.0f;
}


