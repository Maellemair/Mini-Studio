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

	bg = CreateRectangle<Background>(pSizeWin.y, pSizeWin.x, sf::Color::Red);
	bg->Load("Background");

	cam = GameManager::Get()->GetView();
	cam->zoom(0.75f);
	sf::Vector2f camSize = cam->getSize();
	cam->setCenter(camSize.x / 2, 720 - camSize.y / 2);

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
	
	mObjectType['r'] = new Rocks();

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
	mMusic->Load("../../../res/f1_intro.ogg");
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

	float minX = camSize.x / 2;
	float maxX = 1280 - camSize.x / 2;
	float minY = camSize.y / 2;
	float maxY = 720 - camSize.y / 2;

	float newCamX = std::clamp(pPos.x, minX, maxX);
	float newCamY = std::clamp(pPos.y, minY, maxY);

	cam->setCenter(newCamX, newCamY);

	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
		mPlateforms[i]->PrintCollider(sf::Color::White);
		pEntity1->PrintCollider(sf::Color::White);
	}
}