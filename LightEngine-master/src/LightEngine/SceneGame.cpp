#include "SceneGame.h"
#include <iostream>
#include "DummyEntity.h"

#include "Debug.h"

void SceneGame::OnInitialize()
{
	pPlayer = CreateEntity<DummyEntity>(20, sf::Color::Red);
	pPlayer->SetPosition(100, 100);
	pPlayer->SetRigidBody(true);

}

void SceneGame::OnEvent(const sf::Event& event)
{

	if (event.JoystickConnected) {

		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		float vitesse = 2.f;

		

		if (sf::Joystick::isButtonPressed(0, 7))
		{
			vitesse = vitesse * 2;
			std::cout << "Bouton 1" << std::endl;

		}

		pPlayer->SetDirection(x, y, vitesse);

	}


	

}

void SceneGame::OnUpdate()
{
	
}