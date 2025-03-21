#pragma once

#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	
	if (mpScene)
	{
		mpScene->OnDestroy();
		delete mpScene;
		mpScene = nullptr;
	}

	T* newScene = new T();
	mpScene = newScene;

	mpScene->SetGameManager(this);
	mpScene->OnInitialize();

	Run();
}
