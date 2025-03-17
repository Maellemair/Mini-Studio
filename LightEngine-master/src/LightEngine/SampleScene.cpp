#include "SampleScene.h"

#include "Player.h"
#include "Bullets.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"
#include "MapEditor.h"
#include "Enemy.h"
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

	pEnemy = CreateRectangle<Enemy>(16, 16, sf::Color::Green);
	pEnemy->SetPosition(200, 100);
	pEnemy->SetCollider(200, 100, 16, 16);
	pEnemy->SetRigidBody(true);


}

void SampleScene::OnEvent(const sf::Event& event)
{
    // Controller inputs
    if (sf::Joystick::isConnected(0))
    {
        pEntity1->dashCooldown += GetDeltaTime(); 
        pEntity1->shootCooldown += GetDeltaTime();
        float vitesse = 250;
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

        // Drift out
        if ((x > 0.f && x < 10.f) || (x < 0.f && x > -10.f))
        {
            x = 0;
        }

        // Boutton X
        if (sf::Joystick::isButtonPressed(0, 1)) {
            pEntity1->Jump();
        }

        // Shoot bullets
        if (sf::Joystick::isButtonPressed(0, 0))
        {
            if (pEntity1->shootCooldown >= 0.2f)
            {
                pBullets = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
                pBullets->SetPosition(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
                pBullets->SetRigidBody(true);
                // Shoot right
                if (pEntity1->getLastDirection() == 1)
                {
                    pBullets->SetDirection(1, 0, 500);
                }
                // Shoot left
                else if (pEntity1->getLastDirection() == -1)
                {
                    pBullets->SetDirection(-1, 0, 500);
                }
                pEntity1->shootCooldown = 0;
            }
        }

        // Joystick a Droite
        if (x > 10.f)
        {
            pEntity1->Move(GetDeltaTime(), 1);
            pEntity1->setLastDirection(1);
        }
        // Joystick a Gauche
        else if (x < -10.f)
        {
            pEntity1->Move(GetDeltaTime(), -1);
            pEntity1->setLastDirection(-1);
        }
        // Rien
        else
        {
            pEntity1->Move(GetDeltaTime(), 0);
        }

        // Boutton R2
        if (pEntity1->dashCooldown >= 2.0f) // Correction de la condition
        {
            if (sf::Joystick::isButtonPressed(0, 7))
            {
                pEntity1->dashTimer += GetDeltaTime();
                if (pEntity1->dashTimer < pEntity1->dashTime)
                {
                    std::cout << "Dashing with direction: " << pEntity1->getLastDirection() << std::endl;
                    pEntity1->Dash(GetDeltaTime());
                }
                pEntity1->dashCooldown = 0;
            }
        }
        else
        {
            pEntity1->dashTimer = 0; // R�initialiser le dashTimer si le cooldown n'est pas encore termin�
        }
    }

    // Keyboard inputs
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

        // Shoot right
        if (pEntity1->getLastDirection() == 1)
        {
            bullet->SetDirection(1, 0, 500);
        }
        // Shoot left
        else if (pEntity1->getLastDirection() == -1)
        {
            bullet->SetDirection(-1, 0, 500);
        }
    }

    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        pEntity1->Jump();
    }

    // Reset Position
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

	
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
		pEnemy->IsColliding(*ObjectCollider);
	}

	const auto* enemyCollider = pEnemy->GetCollider();
	pEntity1->IsColliding(*enemyCollider);


}