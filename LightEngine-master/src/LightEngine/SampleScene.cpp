#include "SampleScene.h"

#include "PhysicalEntity.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateRectangle<PhysicalEntity>(150, 150, sf::Color::Red);
	pEntity1->SetPosition(600, 100);
	pEntity1->SetRigidBody(true);
	pEntity1->EnableGravity(true);
	struct AABBCollider r1 = { 600.f, 100.f, 750.f, 250.f };

	pEntity2 = CreateRectangle<PhysicalEntity>(150, 150, sf::Color::Green);
	pEntity2->SetPosition(600, 500);
	pEntity2->SetRigidBody(true);
	pEntity2->EnableGravity(false);
	struct AABBCollider r2 = { 600.f, 500.f, 750.f, 650.f };

	float posX = 64;
	float posY = 500;
	/*for (int i = 0; i < 15; i++)
	{
		ObjectEntity* tempEntity = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Yellow);
		mPlateforms.push_back(tempEntity);
		tempEntity->SetPosition(posX, posY);
		tempEntity->SetRigidBody(true);
		posX += 74;
	}*/

	pEntitySelected = nullptr;

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
		TrySetSelectedEntity(pEntity2, event.mouseButton.x, event.mouseButton.y);
	}

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (pEntitySelected != nullptr)
		{
			//pEntitySelected->GoToPosition(event.mouseButton.x, event.mouseButton.y, 100);
			pEntitySelected->Jump();
		}
	}
}

void SampleScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
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

	/*if (pEntity1->IsColliding())
	{
		std::cout << "Colliding" << std::endl;
	}*/
	
}