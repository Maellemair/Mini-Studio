#include "SampleScene.h"

#include "Player.h"
#include "Bullets.h"
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
	//Controller inputs
	if (sf::Joystick::isConnected(0))
	{
		float vitesse = 250;
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

		//Drift out
		if (x > 0.f && x < 10.f || x < 0.f && x > -10.f)
		{
			x = 0;
		}

		//Boutton X
		if (sf::Joystick::isButtonPressed(0, 1)) {
			pEntity1->Jump();
		}

		//Shoot bullets 
		else if (sf::Joystick::isButtonPressed(0, 0))
		{
			Entity* bullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
			bullet->SetPosition(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
			bullet->SetRigidBody(true);

			//Shoot right
			if (pEntity1->getLastDirection() == 1)
			{
				bullet->SetDirection(1, 0, 500);
			}
			//Shoot left
			else if (pEntity1->getLastDirection() == -1)
			{
				bullet->SetDirection(-1, 0, 500);
			}

		}

		//Joystick a Droite
		if (x > 10.f)
		{
			pEntity1->Move(GetDeltaTime(), 1);
			pEntity1->setLastDirection(1);
		}
		//Joystick a Gauche
		else if (x < -10.f)
		{
			pEntity1->Move(GetDeltaTime(), -1);
			pEntity1->setLastDirection(-1);
		}
		//Rien
		else
		{
			pEntity1->Move(GetDeltaTime(), 0);
		}

		//Boutton R2
		pEntity1->dashCooldown += GetDeltaTime();
		if (pEntity1->dashCooldown >= 2.0f)
		{
			if (sf::Joystick::isButtonPressed(0, 7))
			{
				pEntity1->dashTimer += GetDeltaTime();
			
				if (pEntity1->dashTimer < pEntity1->dashTime)
				{
					pEntity1->Dash(GetDeltaTime());
				}
				else
				{
					pEntity1->dashCooldown = 0;
				}
				
			}
			else
			{
				pEntity1->dashTimer = 0;
			}
		}
	}

	//Keyboard inputs
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			pEntity1->Move(GetDeltaTime(), -1);
			pEntity1->setLastDirection(-1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			pEntity1->Move(GetDeltaTime(), 1);
			pEntity1->setLastDirection(1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			Entity* bullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
			bullet->SetPosition(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
			bullet->SetRigidBody(true);

			//Shoot right
			if (pEntity1->getLastDirection() == 1)
			{
				bullet->SetDirection(1, 0, 500);
			}
			//Shoot left
			else if (pEntity1->getLastDirection() == -1)
			{
				bullet->SetDirection(-1, 0, 500);
			}
		}
		
		//Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			pEntity1->Jump();
		}

		//Reset Position
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			pEntity1->Reset();
		}

		if (event.type != sf::Event::EventType::MouseButtonPressed) {
			return;
		}

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
	const char* life = "Life : " + pEntity1->mLife;
	Debug::DrawText(10, 20, "Life : " + pEntity1->mLife, sf::Color::Black);

	//std::cout << pEntity1->GetState() << std::endl;
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
	}
}