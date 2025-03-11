#include "SampleScene.h"

#include "Player.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	pEntity1 = CreateRectangle<Player>(50, 50, sf::Color::Red);
	pEntity1->SetPosition(101, 100);
	pEntity1->SetRigidBody(true);

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

	ObjectEntity* tempEntity = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Yellow);
	mPlateforms.push_back(tempEntity);
	tempEntity->SetPosition(500, 300);
	tempEntity->SetRigidBody(true);
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