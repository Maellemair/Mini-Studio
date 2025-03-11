#include "SceneGame.h"
#include <iostream>
#include "Player.h"
#include "Debug.h"
#include <SFML/Graphics.hpp>

void SceneGame::OnInitialize()
{
    pPlayer = CreateEntity<Player>(20, sf::Color::Red);
    pPlayer->SetPosition(640, 600);
    pPlayer->SetRigidBody(true);

    sf::RectangleShape Rect(sf::Vector2f(200.f, 50.f)); 
    Rect.setFillColor(sf::Color::Blue);
    Rect.setPosition(300.f, 300.f);
    
}

void SceneGame::OnEvent(const sf::Event& event)
{

}

void SceneGame::OnUpdate()
{
    std::string text = "Life : " + std::to_string(pPlayer->GetLife());
    Debug::DrawText(10, 10, text, sf::Color::White);

}
