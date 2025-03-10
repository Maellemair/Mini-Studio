#include "SceneGame.h"
#include <iostream>
#include "DummyEntity.h"

#include "Debug.h"

void SceneGame::OnInitialize()
{
	pPlayer = CreateEntity<DummyEntity>(20, sf::Color::Red);
	pPlayer->SetPosition(640, 600);
	pPlayer->SetRigidBody(true);

}

void SceneGame::OnEvent(const sf::Event& event)
{

	if (event.JoystickConnected) {

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

		pPlayer->SetDirection(x, 0, vitesse);
		std::cout << "X : " << x << std::endl;
	}


}

void SceneGame::OnUpdate()
{
	
}