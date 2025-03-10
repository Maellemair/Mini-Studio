#include "PlatformerScene.h"
#include <iostream>

#include "PhysicalEntity.h"

#include "Debug.h"

void PlatformerScene::OnInitialize()
{
	mWidth = GetWindowWidth();
	mHeight = GetWindowHeight();

	pEntity1 = CreateEntity<PhysicalEntity>(30, sf::Color::Red);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);

	entityRadius = mHeight * 0.05f;
}

void PlatformerScene::OnUpdate()
{
}

void PlatformerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		
	}
}
