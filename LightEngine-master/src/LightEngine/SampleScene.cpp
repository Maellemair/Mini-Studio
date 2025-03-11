#include "SampleScene.h"

#include "PhysicalEntity.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateRectangle<PhysicalEntity>(100, 100, sf::Color::Red);
	pEntity1->SetPosition(100, 100);
	pEntity1->SetRigidBody(true);

	pEntity2 = CreateRectangle<PhysicalEntity>(200, 200, sf::Color::Green);
	pEntity2->SetPosition(500, 500);
	pEntity2->SetRigidBody(true);

	float posX = 64;
	float posY = 500;
	for (int i = 0; i < 15; i++)
	{
		ObjectEntity* tempEntity = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Yellow);
		mPlateforms.push_back(tempEntity);
		tempEntity->SetPosition(posX, posY);
		tempEntity->SetRigidBody(true);
		posX += 74;
	}

	pEntitySelected = nullptr;

}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Right)
	{
		TrySetSelectedEntity(pEntity1, event.mouseButton.x, event.mouseButton.y);
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
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		if (pEntity1->IsColliding(*ObjectCollider))
		{
			std::cout << "collision" << std::endl;
		}
	}
}