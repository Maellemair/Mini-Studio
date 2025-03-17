#include "SampleScene.h"

#include "Player.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"
#include "MapEditor.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	map = new MapEditor();
	map->Load("../../../res/Layout_Test.txt");
	map->CreateMap(64);
	mPlateforms = map->GetMap();

	mMusic = new Music();
	mMusic->Load("../../../res/f1_intro.ogg");
	mMusic->Play();

	pEntity1 = CreateRectangle<Player>(16, 16, sf::Color::Red);
	pEntity1->SetPosition(101, 100);
	pEntity1->SetCollider(101, 100, 16, 16);
	pEntity1->SetRigidBody(true);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
		pEntity1->Reset();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		mMusic->PausePlay();
	}

	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		/*ObjectEntity* tempEntityGrass = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Green);
		mPlateforms.push_back(tempEntityGrass);
		tempEntityGrass->SetPosition(event.mouseButton.x, event.mouseButton.y);
		tempEntityGrass->SetRigidBody(true);*/
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
	//std::cout << pEntity1->GetState() << std::endl;
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
	}
}