#include "Player.h"

void Player::OnInitialize()
{
	mShape->setFillColor(sf::Color::Red);
}

void Player::Move(int key)
{
	SetDirection(key, 0, 250);
}

void Player::Reset()
{
	sf::Vector2f pPosCenter = sf::Vector2f(GameManager::Get()->GetScene()->GetWindowWidth(),
		GameManager::Get()->GetScene()->GetWindowHeight());
	SetPosition(pPosCenter.x / 2, pPosCenter.y / 4);
	SetCollider(pPosCenter.x / 2, pPosCenter.y / 4, mBoxCollider->ySize, mBoxCollider->xSize);
	mGravitySpeed = 0;
}

void Player::Jump()
{
	if (GetState() == TOP || mNbrJump >= 2 || mClockDoubleJump.getElapsedTime().asSeconds() < jumpCooldown)
		return;

	sf::Vector2f pPos = GetPosition(0.5f, 0.5f);
	SetPosition(pPos.x, pPos.y - 1);
	SetCollider(pPos.x, pPos.y - 1, mBoxCollider->ySize, mBoxCollider->xSize);
	mGravity = true;
	mGravitySpeed = -350;
	mNbrJump++;
	mClockDoubleJump.restart();
}
