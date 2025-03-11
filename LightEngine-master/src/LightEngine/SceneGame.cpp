#include "SceneGame.h"
#include <iostream>
#include "Player.h"

#include "Debug.h"

void SceneGame::OnInitialize()
{
	pPlayer = CreateEntity<Player>(20, sf::Color::Red);
	pPlayer->SetPosition(640, 600);
	pPlayer->SetRigidBody(true);
}

void SceneGame::OnEvent(const sf::Event& event)
{

}

void SceneGame::OnUpdate()
{
	std::string text = "Life : " + std::to_string(pPlayer->GetLife());
	Debug::DrawText(10, 10, text, sf::Color::White);
}