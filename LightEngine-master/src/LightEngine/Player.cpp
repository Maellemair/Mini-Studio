#include "Player.h"

void Player::Move(float deltaTime, int key)
{
	SetDirection(key, 0, 250);
}

void Player::Jump()
{
	if (GetState() == TOP || mNbrJump >= 2 || mClockDoubleJump.getElapsedTime().asSeconds() < jumpCooldown)
		return;

	sf::Vector2f pPos = GetPosition(0.5f, 0.5f);
	SetPosition(pPos.x, pPos.y - 1);
	mGravity = true;
	mGravitySpeed = -350;
	mNbrJump++;
	mClockDoubleJump.restart();
}
