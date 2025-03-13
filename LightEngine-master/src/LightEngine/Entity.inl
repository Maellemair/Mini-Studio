#include "Entity.h"

#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}

template<typename T>
T* Entity::CreateRectangle(float height, float width, const sf::Color& color)
{
	return GetScene()->CreateRectangle<T>(height, width, color);
}