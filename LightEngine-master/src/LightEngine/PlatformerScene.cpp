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

	pEntity1->EnableGravity(true);
}

void PlatformerScene::OnUpdate()
{
	std::cout << "GetDeltaTime(): " << GetDeltaTime() << std::endl;
	pEntity1->Fall(GetDeltaTime());
}

void PlatformerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		pEntity1->SetPosition(event.mouseButton.x, event.mouseButton.y);
	}
	else if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		pEntity1->Jump();
	}
}
