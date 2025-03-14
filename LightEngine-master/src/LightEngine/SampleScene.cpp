#include "SampleScene.h"

#include "Player.h"
#include "ObjectEntity.h"
#include "Debug.h"
#include "Music.h"
#include "MapEditor.h"
#include "Grass.h"
#include "Sky.h"
#include "Dirt.h"
#include "Background.h"
#include "AssetManager.h"

#include <iostream>
#include <string>

void SampleScene::OnInitialize()
{
	sf::Vector2f pSizeWin = sf::Vector2f(GetWindowWidth(), GetWindowHeight());

	bg = CreateRectangle<Background>(pSizeWin.x, pSizeWin.y, sf::Color::Red);
	bg->Load("Background");

	mObjectType['-'] = new Sky();
	mObjectType['T'] = new Grass();
	mObjectType['D'] = new Dirt();

	std::vector<std::string> pathLevel = Level::GetInstance()->pathLevel;

	map = new MapEditor();
	map->Load(pathLevel[0].c_str());
	map->CreateMap(64, mObjectType);
	mPlateforms = map->GetMap();

	pEntity1 = CreateRectangle<Player>(16, 16, sf::Color::Red);
	pEntity1->SetPosition(101, 100);
	pEntity1->SetCollider(101, 100, 16, 16);
	pEntity1->SetRigidBody(true);

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

	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		ObjectEntity* tempEntityGrass = CreateRectangle<ObjectEntity>(64, 64, sf::Color::Green);
		mPlateforms.push_back(tempEntityGrass);
		tempEntityGrass->SetPosition(event.mouseButton.x, event.mouseButton.y);
		tempEntityGrass->SetCollider(event.mouseButton.x, event.mouseButton.y, 64, 64);
		tempEntityGrass->SetRigidBody(true);
	}
}

void SampleScene::OnUpdate()
{
	//std::cout << pEntity1->GetState() << std::endl;
	for (int i = 0; i < mPlateforms.size(); i++)
	{
		const auto* ObjectCollider = mPlateforms[i]->GetCollider();
		pEntity1->IsColliding(*ObjectCollider);
	}
}