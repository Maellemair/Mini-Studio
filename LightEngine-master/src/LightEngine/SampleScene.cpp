#include "SampleScene.h"

#include "Player.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateRectangle<Player>(16, 16, sf::Color::Red);
	pEntity1->SetPosition(101, 100);
	pEntity1->SetRigidBody(true);

	float posX = 32;
	float posY = 624;
	for (int i = 0; i < 20; i++)
	{
		ObjectEntity* tempEntityGrass = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Green);
		mPlateforms.push_back(tempEntityGrass);
		tempEntityGrass->SetPosition(posX, posY);
		tempEntityGrass->SetRigidBody(true);

		ObjectEntity* tempEntityDirt = CreateRectangle<ObjectEntity>(64, 64, sf::Color(88, 41, 0, 255));
		mPlateforms.push_back(tempEntityDirt);
		tempEntityDirt->SetPosition(posX, posY + 64);
		tempEntityDirt->SetRigidBody(true);
		posX += 64;
	}

	ObjectEntity* tempEntityGrass = CreateRectangle<ObjectEntity>(100, 100, sf::Color::Yellow);
	mPlateforms.push_back(tempEntityGrass);
	tempEntityGrass->SetPosition(500, 400);
	tempEntityGrass->SetRigidBody(true);
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		pEntity1->Move(GetDeltaTime(), -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		pEntity1->Move(GetDeltaTime(), 1);
	}
	else{ 
		pEntity1->Move(GetDeltaTime(), 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		pEntity1->Jump();
	}

	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		ObjectEntity* tempEntityGrass = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Green);
		mPlateforms.push_back(tempEntityGrass);
		tempEntityGrass->SetPosition(event.mouseButton.x, event.mouseButton.y);
		tempEntityGrass->SetRigidBody(true);
	}
}

//void SampleScene::TrySetSelectedEntity(PhysicalEntity* pEntity, int x, int y)
//{
//	if (pEntity->IsInside(x, y) == false)
//		return;
//
//	pEntitySelected = pEntity;
//}

void SampleScene::OnUpdate()
{
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
	}
}