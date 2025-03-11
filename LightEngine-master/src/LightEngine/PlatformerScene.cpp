#include "PlatformerScene.h"
#include <iostream>

#include "PhysicalEntity.h"

#include "Debug.h"

void PlatformerScene::OnInitialize()
{
	mWidth = GetWindowWidth();
	mHeight = GetWindowHeight();

	pEntity1 = CreateEntity<PhysicalEntity>(50, sf::Color::Red);
	pEntity1->SetPosition(500, 500);
	pEntity1->SetRigidBody(true);

	pEntity1->EnableGravity(true);
}

void PlatformerScene::OnUpdate()
{
	//pEntity1->BottomEdgeCollision(mHeight);
}

void PlatformerScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		pEntity1->EnableGravity(false);
		pEntity1->SetPosition(event.mouseButton.x, event.mouseButton.y);
		pEntity1->EnableGravity(true);
	}
	else if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		pEntity1->Jump();
	}
}
