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
#include "Assets/DeathZone.h"

#include "Player.h"
#include "Bullets.h"
#include "BulletsEnemy.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Hearth.h"
#include "Reservoir.h"
#include "Bonus.h"

#include "Music.h"
#include "Sound.h"
#include "MapEditor.h"
#include "AssetManager.h"
#include "Utils.h"

#include "Enemy.h"
#include "EnemyVolant.h"
#include "EnemyGround.h"
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
	cam->zoom(0.6f);
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
		mObjectType['Z'] = new DeathZone();

	}

	std::vector<std::string> pathLevel = Level::GetInstance()->pathLevel;

	pEntity1 = CreateRectangle<Player>(64, 64, sf::Color::Red);
	pEntity1->SetPosition(101, 550);
	pEntity1->SetCollider(101, 550, 64, 45);
	pEntity1->SetRigidBody(true);

	map = new MapEditor();
	map->Load(pathLevel[0].c_str());
	map->CreateMap(32, mObjectType);

	mPlateforms = map->GetMap();
    mEnemys = map->GetEnemy();
    mBonus = map->GetBonus();

    mReservoir = CreateRectangle<Reservoir>(58, 34, sf::Color::Red);

	mMusic = new Music();
	mMusic->Load("../../../res/platformer_music.wav", 10);
	mMusic->Play();
}

void SampleScene::OnEvent(const sf::Event& event)
{
    //Controller inputs
    if (sf::Joystick::isConnected(0))
    {
        float vitesse = 250;
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

        // Drift out
        if ((x > 0.f && x < 10.f) || (x < 0.f && x > -10.f))
        {
            x = 0;
        }
        //Boutton X
        if (sf::Joystick::isButtonPressed(0, 1)) {
            pEntity1->Jump();
        }

        //Bouton Carré
        else if (sf::Joystick::isButtonPressed(0, 0))
        {
            if (!pEntity1->GetIsShooting() && pEntity1->GetAmmo() > 0)
            {
                Bullets* newBullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
                sf::Vector2f pPos = sf::Vector2f(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
                sf::Vector2f colliderX = sf::Vector2f(pEntity1->GetCollider()->xMin, pEntity1->GetCollider()->xMax);

                if (pEntity1->getLastDirection() == 1)
                {
                    newBullet->SetPosition(colliderX.y, pPos.y);
                    newBullet->SetCollider(colliderX.y, pPos.y, 8, 16);
                    newBullet->SetDirection(1, 0, 500);
                }
                else if (pEntity1->getLastDirection() == -1)
                {
                    newBullet->SetPosition(colliderX.x, pPos.y);
                    newBullet->SetCollider(colliderX.x, pPos.y, 8, 16);
                    newBullet->SetDirection(-1, 0, 500);
                }
                newBullet->SetRigidBody(true);
                newBullet->Update();

                bulletsList.push_back(newBullet);
                pEntity1->Shoot();
            }
        }
        //Joystick a Droite
        if (x > 10.f)
        {
            pEntity1->Move(1);
            pEntity1->setLastDirection(1);
        }
        //Joystick a Gauche
        else if (x < -10.f)
        {
            pEntity1->Move(-1);
            pEntity1->setLastDirection(-1);
        }
        //Rien
        else
        {
            pEntity1->Move(0);
        }
    }

    //Keyboard inputs
    else 
    {
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
            pEntity1->Move(0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        
        if (!pEntity1->GetIsShooting() && pEntity1->GetAmmo() > 0)
        {
            Bullets* newBullet = CreateRectangle<Bullets>(16, 8, sf::Color::Blue);
            sf::Vector2f pPos = sf::Vector2f(pEntity1->GetPosition().x, pEntity1->GetPosition().y);
            sf::Vector2f colliderX = sf::Vector2f(pEntity1->GetCollider()->xMin, pEntity1->GetCollider()->xMax);

            if (pEntity1->getLastDirection() == 1)
            {
                newBullet->SetPosition(colliderX.y, pPos.y);
                newBullet->SetCollider(colliderX.y, pPos.y, 8, 16);
                newBullet->SetDirection(1, 0, 500);
            }
            else if (pEntity1->getLastDirection() == -1)
            {
                newBullet->SetPosition(colliderX.x, pPos.y);
                newBullet->SetCollider(colliderX.x, pPos.y, 8, 16);
                newBullet->SetDirection(-1, 0, 500);
            }
            newBullet->SetRigidBody(true);
            newBullet->Update();

            bulletsList.push_back(newBullet);
            pEntity1->Shoot();
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
    
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		mMusic->PausePlay();
	}

    if (event.type != sf::Event::EventType::MouseButtonPressed)
        return;
}

void SampleScene::OnUpdate()
{
	sf::Vector2f camSize = cam->getSize();
	sf::Vector2f pPos = pEntity1->GetPosition();
	sf::Vector2f posLimite = sf::Vector2f(20000, 720);

	float minX = camSize.x / 2;
	float maxX = posLimite.x - camSize.x / 2;
	float minY = camSize.y / 2;
	float maxY = posLimite.y - camSize.y / 2;

	float newCamX = std::clamp(pPos.x, minX, maxX);
	float newCamY = std::clamp(pPos.y, minY, maxY);

	cam->setCenter(newCamX, newCamY);
	mCamPos = sf::Vector2f(newCamX, newCamY);

    if (mHearths.size() < pEntity1->GetLife())
    {
        int size = pEntity1->GetLife() - mHearths.size();
        for (int i = 0; i < size; i++)
        {
            Hearth* tempHeart = CreateRectangle<Hearth>(27, 27, sf::Color::Magenta);
            tempHeart->SetPosition(0, 0);
            mHearths.push_back(tempHeart);
        }
    }
    sf::Vector2f HearthPos = sf::Vector2f(newCamX - camSize.x / 2 + 30, newCamY - camSize.y / 2 + 30);
    for (int i = 0; i < mHearths.size(); i++)
    {
        if (pEntity1->GetLife() < i + 1)
        {
            mHearths[i]->SetDead(true);
        }
        else
        {
            mHearths[i]->SetDead(false);
        }
        mHearths[i]->SetPosition(HearthPos.x, HearthPos.y);
        HearthPos.x += 30;
    }

    mReservoir->SetPosition(newCamX + camSize.x / 2 - 40, newCamY - camSize.y / 2 + 35);
    mReservoir->UpdateText(pEntity1->GetAmmo());

	float deltaX = mCamPos.x - lastCameraPosition.x;
	for (int i = 0; i < mBackgrounds.size(); i++)
	{
		mBackgrounds[i]->OnUpdate(deltaX, newCamX);
	}
    lastCameraPosition = mCamPos;

	for (int i = 0; i < mPlateforms.size(); i++)
	{
		if (mPlateforms[i]->IsColliding(pEntity1))
		{
            if (DeathZone* pPlateform = dynamic_cast<DeathZone*>(mPlateforms[i]))
            {
                pEntity1->TakeHit(0, pEntity1->GetLife());
                pEntity1->SetPosition(pPlateform->GetPosition().x, pPlateform->GetPosition().y + pEntity1->GetColliderSize().y * 3);
            }
			pEntity1->Repulse(mPlateforms[i]);
		}
		else
		{
			mPlateforms[i]->SetStateCollision(None);
		}

        for (int j = 0; j < mEnemys.size(); j++)
        {
            if (mPlateforms[i]->IsColliding(mEnemys[j]))
            {
                mEnemys[j]->Repulse(mPlateforms[i]);
            }
            //mEnemys[j]->PrintCollider(sf::Color::White);
        }

        for (int j = 0; j < bulletsList.size(); j++)
        {
            if (bulletsList[j]->IsColliding(mPlateforms[i]))
            {
                bulletsList[j]->Destroy();
                bulletsList.erase(bulletsList.begin() + j);
                j--;
            }
        }

        for (int j = 0; j < bulletsEnemyList.size(); j++)
        {
            if (bulletsEnemyList[j]->IsColliding(mPlateforms[i]))
            {
                bulletsEnemyList[j]->Destroy();
                bulletsEnemyList.erase(bulletsEnemyList.begin() + j);
                j--;
            }
        }
		/*mPlateforms[i]->PrintCollider(sf::Color::White);
		pEntity1->PrintCollider(sf::Color::White);*/
	}

    for(int i = 0; i < mEnemys.size(); i++)
    {
        if (pEntity1->IsColliding(mEnemys[i]))
        {
            if (pEntity1->invicibilityTime > 1.5f)
            {
                if (!pEntity1->IsDead() && !mEnemys[i]->IsDead())
                {
                    pEntity1->TakeHit(mEnemys[i]->GetPosition().x);
                    float direction = (pEntity1->GetPosition().x - mEnemys[i]->GetPosition().x) / abs(pEntity1->GetPosition().x - mEnemys[i]->GetPosition().x);
                    mEnemys[i]->Attack(direction);
                }
            }
        }
        else
        {
            if (EnemyVolant* pEnemy = dynamic_cast<EnemyVolant*>(mEnemys[i]))
            {
                if (pEntity1->GetPosition().y > pEnemy->GetPosition().y && pEntity1->GetPosition().y < pEnemy->GetPosition().y + 100)
                {
                    sf::Vector2f enemyPos = pEnemy->GetPosition();
                    sf::Vector2f pPos = pEntity1->GetPosition();
                    float distance = Utils::GetDistance(enemyPos.x, enemyPos.y, pPos.x, pPos.y);
                    if (distance <= 200)
                    {
                        pEnemy->Tracking(pPos.x);
                        if(!pEnemy->GetIsAttacking())
                        {
                            pEnemy->Attack(0);

                            BulletsEnemy* newBulletLeft = CreateRectangle<BulletsEnemy>(18, 18, sf::Color::Blue);
                            sf::Vector2f pPos = sf::Vector2f(pEnemy->GetPosition().x, pEnemy->GetPosition().y);
                            newBulletLeft->SetPosition(pPos.x, pPos.y);
                            newBulletLeft->SetCollider(pPos.x, pPos.y, 18, 18);
                            newBulletLeft->SetDirection(0, 1, 300);
                            bulletsEnemyList.push_back(newBulletLeft);
                        }
                    }
                }
                else
                {
                    pEnemy->SetDirection(0, 0);
                }
            }
            pEntity1->invicibilityTime += GetDeltaTime();
        }
        for(int j = 0; j < bulletsList.size(); j++)
        {
            /*bulletsList[j]->PrintCollider(sf::Color::Magenta);*/
            
            if (bulletsList[j]->IsColliding(mEnemys[i]) && !mEnemys[i]->IsDead())
            {
                mEnemys[i]->Hit();

                bulletsList[j]->Destroy();
                bulletsList.erase(bulletsList.begin() + j);
                j--;
                break;
            }
        }
    }
    
    for (int i = 0; i < bulletsEnemyList.size(); i++)
    {
        if (bulletsEnemyList[i]->IsColliding(pEntity1))
        {
            pEntity1->TakeHit(bulletsEnemyList[i]->GetPosition().x);
            bulletsEnemyList[i]->Destroy();
            bulletsEnemyList.erase(bulletsEnemyList.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < mBonus.size(); i++)
    {
        if (pEntity1->IsColliding(mBonus[i]))
        {
            mBonus[i]->isCollid(pEntity1);
            mBonus[i]->Destroy();
            mBonus.erase(mBonus.begin() + i);
            i--;
        }
    }
}