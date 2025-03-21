#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy() {};

public:
	/*template<typename T>
	T* CreateCircle(float radius, const sf::Color& color);*/
	template<typename T>
	T* CreateRectangle(float height, float width, const sf::Color& color);

	float GetDeltaTime() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"