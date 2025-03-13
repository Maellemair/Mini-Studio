#include "SampleScene.h"

#include "Player.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"
#include "MapEditor.h"

#include <iostream>

void SampleScene::OnInitialize()
{
	map = new MapEditor();
	map->Load("../../../res/Layout_Test.txt");
	map->CreateMap(64);
	mPlateforms = map->GetMap();

	pEntity1 = CreateRectangle<Player>(16, 16, sf::Color::Red);
	pEntity1->SetPosition(101, 100);
	pEntity1->SetCollider(101, 100, 16, 16);
	pEntity1->SetRigidBody(true);

}

void SampleScene::OnEvent(const sf::Event& event)
{
	
	if (sf::Joystick::isConnected(0))
	{
		float vitesse = 250;
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

		if (x > 0.f && x < 10.f || x < 0.f && x > -10.f)
		{
			x = 0;
		}

		if (sf::Joystick::isButtonPressed(0, 7))
		{
			vitesse = vitesse * 1.25f;
		}

		if (x > 10.f)
		{
			pEntity1->Move(GetDeltaTime(), 1);
		}
		else if (x < -10.f)
		{
			pEntity1->Move(GetDeltaTime(), -1);
		}
		else
		{
			pEntity1->Move(GetDeltaTime(), 0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		pEntity1->Move(GetDeltaTime(), -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		pEntity1->Move(GetDeltaTime(), 1);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Joystick::isButtonPressed(0, 1)) {
		pEntity1->Jump();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
		pEntity1->Reset();
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