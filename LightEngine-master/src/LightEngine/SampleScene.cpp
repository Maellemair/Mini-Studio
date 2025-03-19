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
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"
#include "Sound.h"
#include "MapEditor.h"
#include "AssetManager.h"
#include "Utils.h"

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
	pEntity1->SetPosition(101, 100);
	pEntity1->SetCollider(101, 100, 64, 45);
	pEntity1->SetRigidBody(true);

	map = new MapEditor();
	map->Load(pathLevel[0].c_str());
	map->CreateMap(32, mObjectType);
	mPlateforms = map->GetMap();

	mMusic = new Music();
	mMusic->Load("../../../res/f1_intro.ogg", 1);
	mMusic->Play();
}

void SampleScene::OnEvent(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		pEntity1->Move(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		pEntity1->Move(1);
	}
	else{ 
		pEntity1->Move(0);
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
}

void SampleScene::OnUpdate()
{
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
		mPlateforms[i]->PrintCollider(sf::Color::White);
		pEntity1->PrintCollider(sf::Color::White);
	}
}