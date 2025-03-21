#include "BulletsEnemy.h"
#include "AssetManager.h"

void BulletsEnemy::OnInitialize()
{
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["hud/eau"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 18), sf::Vector2i(9, 9)));
	mShape->rotate(90);

	animBullets = new Animation;
	animBullets->loadAnimations(m["hud/eau"], "../../../res/BulletsEnemy.json", mShape);
	animBullets->setAnimation("idle");
}

void BulletsEnemy::OnUpdate()
{
	float dt = GetDeltaTime();
	animBullets->update(dt);
	mGravitySpeed = -70.0f;
}
