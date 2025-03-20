#include "SampleScene.h"

#include "Assets/Grass.h"
#include "Assets/Dirt.h"
#include "Assets/Right_edge_grass.h"
#include "Assets/Left_edge_grass.h"
#include "Assets/Left_edge_dirt.h"
#include "Assets/Right_edge_dirt.h"
#include "Assets/Plateform.h"
#include "Assets/Plateform_middle.h"
#include "Assets/Plateform_edge_right.h"
#include "Assets/Plateform_edge_left.h"
#include "Assets/Rocks.h"
#include "Assets/Background.h"
#include "Assets/Left_dirt_fall.h"
#include "Assets/Right_dirt_fall.h"

#include "Player.h"
#include "Bullets.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Bonus.h"
#include "Music.h"
#include "Sound.h"
#include "MapEditor.h"
#include "AssetManager.h"
#include "Utils.h"

#include "Enemy.h"
#include <iostream>
#include <string>

void SampleScene::OnInitialize()
{
	sf::Vector2f pSizeWin = sf::Vector2f(GetWindowWidth(), GetWindowHeight());

	//Background
	{
		float taille = pSizeWin.y;
		float factor = taille / 180;
		sf::Vector2f tempPos = sf::Vector2f(pSizeWin.x / 2, pSizeWin.y / 2);
		bg = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		bg->Load("Background", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.01, tempPos);
		bg->SetPosition(tempPos.x, tempPos.y);
		mBackgrounds.push_back(bg);

		bg2 = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		bg2->Load("Background", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.01, tempPos);
		bg2->SetPosition(tempPos.x + 320 * factor, tempPos.y);
		mBackgrounds.push_back(bg2);

		factor = taille / 180;
		filtre = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		filtre->Load("filtre", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.01, tempPos);
		filtre->SetPosition(tempPos.x, tempPos.y);
		mBackgrounds.push_back(filtre);

		filtre2 = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		filtre2->Load("filtre", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.01, tempPos);
		filtre2->SetPosition(tempPos.x + 320 * factor, tempPos.y);
		mBackgrounds.push_back(filtre2);

		factor = taille / (360 / 2);
		arbreBack = CreateRectangle<Background>(360 / 2 * factor, 570 * factor, sf::Color::Red);
		arbreBack->Load("Tree", sf::Vector2i(570, 360 / 2), sf::Vector2i(0, 360 / 2), 0.05, tempPos);
		arbreBack->SetPosition(tempPos.x, tempPos.y);
		mBackgrounds.push_back(arbreBack);

		arbreBack2 = CreateRectangle<Background>(360 / 2 * factor, 570 * factor, sf::Color::Red);
		arbreBack2->Load("Tree", sf::Vector2i(570, 360 / 2), sf::Vector2i(0, 360 / 2), 0.05, tempPos);
		arbreBack2->SetPosition(tempPos.x + 570 * factor, tempPos.y);
		mBackgrounds.push_back(arbreBack2);

		factor = taille / (360 / 2);
		arbre = CreateRectangle<Background>(360 / 2 * factor, 570 * factor, sf::Color::Red);
		arbre->Load("Tree", sf::Vector2i(570, 360 / 2), sf::Vector2i(0, 0), 0.25, tempPos);
		arbre->SetPosition(tempPos.x, tempPos.y);
		mBackgrounds.push_back(arbre);

		arbre2 = CreateRectangle<Background>(360 / 2 * factor, 570 * factor, sf::Color::Red);
		arbre2->Load("Tree", sf::Vector2i(570, 360 / 2), sf::Vector2i(0, 0), 0.25, tempPos);
		arbre2->SetPosition(tempPos.x + 570 * factor, tempPos.y);
		mBackgrounds.push_back(arbre2);

		factor = taille / 180;
		filtreArbre = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		filtreArbre->Load("filtre", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.25, tempPos);
		filtreArbre->SetPosition(tempPos.x, tempPos.y);
		mBackgrounds.push_back(filtreArbre);

		filtreArbre2 = CreateRectangle<Background>(180 * factor, 320 * factor, sf::Color::Red);
		filtreArbre2->Load("filtre", sf::Vector2i(320, 180), sf::Vector2i(0, 0), 0.25, tempPos);
		filtreArbre2->SetPosition(tempPos.x + 320 * factor, tempPos.y);
		mBackgrounds.push_back(filtreArbre2);
	}


	cam = GameManager::Get()->GetView();
	cam->zoom(0.75f);
	sf::Vector2f camSize = cam->getSize();
	cam->setCenter(camSize.x / 2, 720 - camSize.y / 2);
	mCamPos = sf::Vector2(camSize.x / 2, 720 - camSize.y / 2);
	lastCameraPosition = mCamPos;
	
	//Assets
	{
		mObjectType['G'] = new Grass();
		mObjectType['D'] = new Dirt();
		mObjectType['P'] = new Right_edge_grass();
		mObjectType['C'] = new Left_edge_grass();
		mObjectType['L'] = new Left_edge_dirt();
		mObjectType['R'] = new Right_edge_dirt();
		mObjectType['S'] = new Plateform();
		mObjectType['T'] = new Plateform_middle();
		mObjectType['A'] = new Plateform_edge_right();
		mObjectType['E'] = new Plateform_edge_left();
		mObjectType['I'] = new Left_dirt_fall();
		mObjectType['J'] = new Right_dirt_fall();

	}

	std::vector<std::string> pathLevel = Level::GetInstance()->pathLevel;

	pEntity1 = CreateRectangle<Player>(64, 64, sf::Color::Red);
	pEntity1->SetPosition(100, 600);
	pEntity1->SetCollider(100, 600, 64, 45);
	pEntity1->SetRigidBody(true);

	map = new MapEditor();
	map->Load(pathLevel[0].c_str());
	map->CreateMap(32, mObjectType);
	mPlateforms = map->GetMap();

	mMusic = new Music();
	mMusic->Load("../../../res/f1_intro.ogg", 1);
	mMusic->Play();
	pEnemy = CreateRectangle<Enemy>(16, 16, sf::Color::Green);
	pEnemy->SetPosition(200, 100);
	pEnemy->SetCollider(200, 100, 16, 16);
	pEnemy->SetRigidBody(true);

    pBonus = CreateRectangle<Bonus>(16, 16, sf::Color::Magenta);
    pBonus->SetPosition(500, 100);
    pBonus->SetCollider(500, 100, 16, 16);
}

void SampleScene::DisplayMenu()
{


    std::string Menu = "Press Start to play !";
    Debug::DrawText(360, 500, Menu, sf::Color::Black);


}   

void SampleScene::OnEvent(const sf::Event& event)
{
    if (isMenuActive)
    {
        // Afficher le menu
        DisplayMenu();

        // Vérifier si l'utilisateur veut quitter le menu
        if (sf::Joystick::isButtonPressed(0, 9) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
        {
            isMenuActive = false;
        }
    }
 
    else 
    {
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
                pEntity1->Move(1);
                pEntity1->setLastDirection(1);
            }
            // Joystick a Gauche
            else if (x < -10.f)
            {
                pEntity1->Move(-1);
                pEntity1->setLastDirection(-1);
            }
            else
            {
                pEntity1->Move(0);
            }
        }

        // Keyboard inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            pEntity1->Move(-1);
            pEntity1->setLastDirection(-1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            pEntity1->Move(1);
            pEntity1->setLastDirection(1);
        }
        else
        {
            // pEntity1->Move(0);
        }

        // Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            pEntity1->Jump();
        }

        // Jump
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
            pEntity1->TakeHit();
        }

        // Reset Position
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            pEntity1->Reset();
        }

        if (event.type != sf::Event::EventType::MouseButtonPressed) {
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            mMusic->PausePlay();
        }

        if (event.type != sf::Event::EventType::MouseButtonPressed)
            return;
    }
  
    
}
void SampleScene::OnUpdate()
{

    // Mettre à jour le joueur et les autres entités
    sf::Vector2f camSize = cam->getSize();
    sf::Vector2f pPos = pEntity1->GetPosition();
    sf::Vector2f posLimite = sf::Vector2f(2000, 720);

    float minX = camSize.x / 2;
    float maxX = posLimite.x - camSize.x / 2;
    float minY = camSize.y / 2;
    float maxY = posLimite.y - camSize.y / 2;

    float newCamX = std::clamp(pPos.x, minX, maxX);
    float newCamY = std::clamp(pPos.y, minY, maxY);

    cam->setCenter(newCamX, newCamY);
    mCamPos = sf::Vector2f(newCamX, newCamY);


    float deltaX = mCamPos.x - lastCameraPosition.x;
    for (int i = 0; i < mBackgrounds.size(); i++)
    {
        mBackgrounds[i]->OnUpdate(deltaX);
    }
    lastCameraPosition = mCamPos;

    bool bulletDestroyed = false;
    bool enemyDestroyed = false;
    bool bonusDestroyed = false;

    for (int i = 0; i < mPlateforms.size(); i++)
    {
        if (mPlateforms[i]->IsColliding(pEntity1))
        {
            pEntity1->Repulse(mPlateforms[i]);
        }
        else
        {
            mPlateforms[i]->SetStateCollision(None);
        }

        if (pEnemy != nullptr && !enemyDestroyed)
        {
            if (mPlateforms[i]->IsColliding(pEnemy))
            {
                pEnemy->Repulse(mPlateforms[i]);
            }
        }

        for (auto it = bulletsList.begin(); it != bulletsList.end();)
        {
            if ((*it)->IsColliding(mPlateforms[i]))
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


    if (isMenuActive)
    {
        DisplayMenu();
    }
    else
    {
       
        std::string life = "Life : " + std::to_string(pEntity1->mLife);
        Debug::DrawText(newCamX - camSize.x / 2 + 10, newCamY - camSize.y / 2 + 20, life, sf::Color::Black);

       

        if (pEnemy != nullptr && !enemyDestroyed)
        {
            if (pEntity1->IsColliding(pEnemy))
            {
                if (pEntity1->invicibilityTime > 1.5f)
                {
                    if (pEntity1->mLife > 0)
                    {
                        pEntity1->mLife -= 1;
                        pEntity1->invicibilityTime = 0.0f;

                        sf::Vector2f repulsionForce;
                        if (pEntity1->GetPosition().x < pEnemy->GetPosition().x)
                        {
                            repulsionForce = sf::Vector2f(-1.f, -1.f);
                        }
                        else
                        {
                            repulsionForce = sf::Vector2f(1, -1.f);
                        }
                        pEntity1->SetDirection(repulsionForce.x, repulsionForce.y, 500.f);
                        pEntity1->repulsionTimer = 0.2f;
                    }
                    else
                    {
                        pEntity1->Destroy();
                        pEntity1 = nullptr;
                    }
                }
            }
            else
            {
                pEntity1->invicibilityTime += GetDeltaTime();
            }
        }

        if (pEntity1 != nullptr && pEntity1->repulsionTimer > 0.0f)
        {
            pEntity1->repulsionTimer -= GetDeltaTime();
            if (pEntity1->repulsionTimer <= 0.0f)
            {
                pEntity1->Move(0);
            }
        }

        if (pEnemy != nullptr && !enemyDestroyed)
        {
            for (auto it = bulletsList.begin(); it != bulletsList.end();)
            {
                if ((*it)->IsColliding(pEnemy))
                {
                    (*it)->Destroy();
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

        if (pBonus != nullptr && !bonusDestroyed)
        {
            if (pEntity1->IsColliding(pBonus))
            {
                pBonus->Destroy();
                pBonus = nullptr;
                pEntity1->mLife++;
                bonusDestroyed = true;
            }
        }

        if (enemyDestroyed)
        {
            pEnemy = nullptr;
        }

        if (pEntity1 != nullptr)
        {
            // Dash boutton R2
            pEntity1->dashCooldown += GetDeltaTime();
            if (pEntity1->dashCooldown >= 2.5f)
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
                        pEntity1->dashCooldown = 0;
                        pEntity1->dashTimer = 0;
                    }
                }
            }
            else
            {
                pEntity1->dashTimer = 0;
            }

            // Shoot bullets
            pEntity1->shootCooldown += GetDeltaTime();
            if (sf::Joystick::isButtonPressed(0, 0) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
            {
                if (pEntity1->shootCooldown >= 0.2f)
                {
                    Bullets* newBullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
                    newBullet->SetPosition(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
                    newBullet->SetCollider(pEntity1->GetPosition().x, pEntity1->GetPosition().y, 8, 16);
                    newBullet->SetRigidBody(true);
                    newBullet->Update();

                    bulletsList.push_back(newBullet);

                    if (pEntity1->getLastDirection() == 1)
                    {
                        newBullet->SetDirection(1, 0, 500);
                    }
                    else if (pEntity1->getLastDirection() == -1)
                    {
                        newBullet->SetDirection(-1, 0, 500);
                    }

                    pEntity1->shootCooldown = 0;
                }
            }
        }
    }
}