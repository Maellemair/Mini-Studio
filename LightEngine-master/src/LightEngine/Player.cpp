#include "Player.h"

void Player::Fall(float deltaTime)
{
	float gravity = 9.81f;
	float speed = 25.f;
	sf::Vector2f pPos = GetPosition();

	mGravitySpeed += speed * gravity * deltaTime;
	pPos.y += mGravitySpeed * deltaTime;

	if (pPos.y > 600)
	{
		pPos.y = 600;
		mGravitySpeed = 0;
	}

	SetPosition(pPos.x, pPos.y);
}

void Player::Jump()
{
	sf::Vector2f mPos = GetPosition();

	if (sf::Joystick::isButtonPressed(0, 1) && !isJumping)
	{
		if (jumpCount < 2)
		{
			mGravitySpeed -= 200;
			isJumping = true;
			std::cout << "Jump" << std::endl;
			jumpCount++;
		}

		else if (mPos.y == 600)
		{
			jumpCount = 0;
		}

	}
	else if (!sf::Joystick::isButtonPressed(0, 1))
	{
		isJumping = false;
	}
}

void Player::Move()
{
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float vitesse = 2.f;
	//Drift out 
	if (x > 0.f && x < 10.f || x < 0.f && x > -10.f)
	{
		x = 0.f;
	}
	//Boutton R2 Appuyé = sprint
	if (sf::Joystick::isButtonPressed(0, 7))
	{
		vitesse = vitesse * 2;
		std::cout << "Bouton 1" << std::endl;
	}
	SetDirection(x, 0, vitesse);
	std::cout << "X : " << x << std::endl;
}

void Player::TakeHit()
{
	Life--;
	if (Life <= 0)
	{
		//GameOver
	}
}

void Player::OnUpdate()
{
	float dt = GetDeltaTime();
	Fall(dt);
	Jump();
	Move();	
}

