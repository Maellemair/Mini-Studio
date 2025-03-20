#include "Enemy.h"
#include "AssetManager.h"
#include "StateMachine.h"

void Enemy::OnInitialize()
{
	SetTag(16);
	std::map <std::string, sf::Texture>& m = Texture::GetInstance()->textObject;
	mShape->setTexture(&m["animation_Player"], true);
	mShape->setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));

	animEnemy = new Animation;
	animEnemy->loadAnimations(m["animation_Ennemy"], "../../../res/Enemy.json", mShape);
	mpStateMachine = new StateMachine<Enemy>(this, State::Count);
}

void Enemy::OnCollision(Entity* collidedWith)
{

}

const char* Enemy::GetStateName(State state) const
{
	switch (state)
	{
	case EVIL: return "Evil";
	case KICK: return "Kick";
	case HIT: return "Hit";
	case NICE: return "Nice";
	default: return "Unknown";
	}
}

void Enemy::OnUpdate()
{

}

