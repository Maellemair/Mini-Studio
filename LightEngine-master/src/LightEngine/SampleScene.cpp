#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	pEntity1 = CreateEntity<DummyEntity>(100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateEntity<DummyEntity>(50, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const sf::Event& event)
{

	if (event.JoystickConnected) {
		if (sf::Joystick::isButtonPressed(0, 20))
		{
			// oui : on shoot !!
		std:: cout << "Bouton 1 appuyé" << std::endl;
		}
		
	}


	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	pEntity1->SetDirection(x, y, 10.f);

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr) 
		{
			pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100.f);
		}
	}
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	if(pEntitySelected != nullptr)
	{
		sf::Vector2f position = pEntitySelected->GetPosition();
		Debug::DrawCircle(position.x, position.y, 10, sf::Color::Blue);
	}
}