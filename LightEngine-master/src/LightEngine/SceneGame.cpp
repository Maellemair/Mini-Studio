#include "SceneGame.h"
#include <iostream>
#include "Player.h"
#include "Debug.h"
#include "Base.h"
#include <SFML/Graphics.hpp>

void SceneGame::OnInitialize()
{
    pPlayer = CreateEntity<Player>(20, sf::Color::Red);
    pPlayer->SetPosition(640, 600);
    pPlayer->SetRigidBody(true);

	Base* pBase = CreateRectangle<Base>(200, 50 sf::Color::Green);
	pBase->SetPosition(640, 700);
}

void SceneGame::OnEvent(const sf::Event& event)
{

}

void SceneGame::OnUpdate()
{
    std::string text = "Life : " + std::to_string(pPlayer->GetLife());
    Debug::DrawText(10, 10, text, sf::Color::White);

}
