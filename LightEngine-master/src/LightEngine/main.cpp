
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "SampleScene.h"
#include "SceneGame.h"

#include <cstdlib>
#include <crtdbg.h>

int main() 
{
    GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "SceneGame", 60, sf::Color::Black);
	
	pInstance->LaunchScene<SceneGame>();

	

	return 0;
}