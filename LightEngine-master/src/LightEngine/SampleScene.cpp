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
    std::string life = "Life : " + std::to_string(pEntity1->mLife);
    Debug::DrawText(10, 20, life, sf::Color::Black);

    bool bulletDestroyed = false;
    bool enemyDestroyed = false;

    // Vérification des collisions avec les plateformes
    for (int i = 0; i < mPlateforms.size(); i++)
    {
        const auto* ObjectCollider = mPlateforms[i]->GetCollider();
        pEntity1->IsColliding(*ObjectCollider);

        if (pEnemy != nullptr && !enemyDestroyed)
        {
            pEnemy->IsColliding(*ObjectCollider);
        }

        for (auto it = bulletsList.begin(); it != bulletsList.end();)
        {
            if ((*it)->IsColliding(*ObjectCollider))
            {
                (*it)->Destroy();
                it = bulletsList.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    if (pEnemy != nullptr && !enemyDestroyed)
    {
        const auto* enemyCollider = pEnemy->GetCollider();
        if (pEntity1->IsColliding(*enemyCollider))
        {
            if (pEntity1->invicibilityTime > 1.5f)
            {
                if (pEntity1->mLife > 0)
                {
                    pEntity1->mLife -= 1;
                    pEntity1->invicibilityTime = 0.0f;

                    // Repousser le joueur
                    sf::Vector2f repulsionForce;
                    if (pEntity1->GetPosition().x < pEnemy->GetPosition().x)
                    {
                        repulsionForce = sf::Vector2f(-75.f, 0.f);
                    }
                    else
                    {
                        repulsionForce = sf::Vector2f(75.f, 0.f);
                    }
                    pEntity1->SetDirection(repulsionForce.x, repulsionForce.y, 300.f);
                    pEntity1->repulsionTimer = 1.0f;
                }
                else
                {
                    // GameOver
                }
            }
        }
        else
        {
            pEntity1->invicibilityTime += GetDeltaTime();
        }
    }

    if (pEntity1->repulsionTimer > 0.0f)
    {
        pEntity1->repulsionTimer -= GetDeltaTime();
        if (pEntity1->repulsionTimer <= 0.0f)
        {
            pEntity1->SetDirection(0.f, 0.f, 0.f); // Arrêter la repulsion après 1 seconde
        }
    }

    // Vérification des collisions entre les balles et l'ennemi
    if (pEnemy != nullptr && !enemyDestroyed)
    {
        const auto* enemyCollider = pEnemy->GetCollider();
        for (auto it = bulletsList.begin(); it != bulletsList.end();)
        {
            if ((*it)->IsColliding(*enemyCollider))
            {
                pEnemy->Destroy();
                enemyDestroyed = true;
                it = bulletsList.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    // Mise à jour de l'état de l'ennemi
    if (enemyDestroyed)
    {
        pEnemy = nullptr; // Assurez-vous de ne plus référencer le pointeur détruit
    }

    // Dash boutton R2
    pEntity1->dashCooldown += GetDeltaTime();
    if (pEntity1->dashCooldown >= 2.5f) // Correction de la condition
    {
        if (sf::Joystick::isButtonPressed(0, 7))
        {
            if (pEntity1->dashTimer < pEntity1->dashTime)
            {
                pEntity1->dashTimer += GetDeltaTime();
                pEntity1->Dash(GetDeltaTime());
            }
            else
            {
                pEntity1->dashCooldown = 0; // Réinitialiser le dashCooldown après le dash
                pEntity1->dashTimer = 0;
            }
        }
    }
    else
    {
        pEntity1->dashTimer = 0; // Réinitialiser le dashTimer si le cooldown n'est pas encore terminé
    }

    // Shoot bullets
    pEntity1->shootCooldown += GetDeltaTime();
    if (sf::Joystick::isButtonPressed(0, 0))
    {
        if (pEntity1->shootCooldown >= 0.2f)
        {
            Bullets* newBullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
            newBullet->SetPosition(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
            newBullet->SetCollider(pEntity1->GetPosition().x, pEntity1->GetPosition().y, 8, 16);
            newBullet->SetRigidBody(true);
            bulletsList.push_back(newBullet);

            // Shoot right
            if (pEntity1->getLastDirection() == 1)
            {
                newBullet->SetDirection(1, 0, 500);
            }
            // Shoot left
            else if (pEntity1->getLastDirection() == -1)
            {
                newBullet->SetDirection(-1, 0, 500);
            }

            pEntity1->shootCooldown = 0;
        }
    }
}
