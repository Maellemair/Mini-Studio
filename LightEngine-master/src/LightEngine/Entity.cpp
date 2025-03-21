#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"
#include "Player.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

void Entity::InitializeRect(float height, float width, const sf::Color& color)
{
	mShape = new sf::RectangleShape;
	
	mShape->setSize(sf::Vector2f(width, height));
	mShape->setOrigin(0.f, 0.f);

	mBoxCollider = new AABBCollider;

	mTarget.isSet = false;
	OnInitialize();
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;
	
	float height = mShape->getSize().y;
	float width = mShape->getSize().x;

	return (dx * dx + dy * dy) < ( height * width);
}

bool Entity::IsColliding(Entity* other) const
{
	AABBCollider* c1 = other->GetCollider();
	if (c1->xMin < mBoxCollider->xMax && c1->xMax > mBoxCollider->xMin &&
		c1->yMin < mBoxCollider->yMax && c1->yMax > mBoxCollider->yMin)
	{
		return true;
	}
	return false;
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = mShape->getPosition();

	float height = mShape->getSize().y;
	float width = mShape->getSize().x;

	position.x += width * ratioX;
	position.y += height * ratioY;

	return position;
}

sf::Vector2f Entity::GetColliderPos(float ratioX, float ratioY) const
{
	sf::Vector2f position = sf::Vector2f(mBoxCollider->xMin, mBoxCollider->yMin);

	float height = mBoxCollider->yMax - mBoxCollider->yMin;
	float width = mBoxCollider->xMax - mBoxCollider->xMin;

	position.x += width * ratioX;
	position.y += height * ratioY;

	return position;
}

sf::Vector2f Entity::GetColliderSize()
{
	sf::Vector2f size;

	size.x = mBoxCollider->xMax - mBoxCollider->xMin;
	size.y = mBoxCollider->yMax - mBoxCollider->yMin;

	return size;
}

bool Entity::GoToDirection(int x, int y, float speed)
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);
	
	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	SetDirection(direction.x, direction.y, speed);

	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	sf::Vector2f size = mShape->getSize();
	x -= size.x / 2;
	y -= size.y / 2;

	sf::Vector2f pPos = GetPosition();

	mShape->setPosition(x, y);

	//#TODO Optimise
	if (mTarget.isSet)
	{
		sf::Vector2f position = GetPosition(0.5f, 0.5f);
		mTarget.distance = Utils::GetDistance(position.x, position.y, mTarget.position.x, mTarget.position.y);
		GoToDirection(mTarget.position.x, mTarget.position.y);
		mTarget.isSet = true;
	}
}

void Entity::SetCollider(float posX, float posY, float height, float width)
{
	mBoxCollider->xMin = posX - width / 2;
	mBoxCollider->xMax = mBoxCollider->xMin + width;
	mBoxCollider->yMin = posY - height / 2;
	mBoxCollider->yMax = mBoxCollider->yMin + height;
	mBoxCollider->xSize = width;
	mBoxCollider->ySize = height;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

void Entity::PrintCollider(sf::Color color)
{
	sf::Vector2 ColliderSize = GetColliderSize();
	Debug::DrawRectangle(mBoxCollider->xMin, mBoxCollider->yMin, ColliderSize.x, ColliderSize.y, color);
}

float Entity::GetHeight() const
{
	return mShape->getSize().y;
}

float Entity::GetWidth() const
{
	return mShape->getSize().x;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;

	mBoxCollider->xMin += translation.x;
	mBoxCollider->xMax += translation.x;
	mBoxCollider->yMin += translation.y;
	mBoxCollider->yMax += translation.y;
	
	mShape->move(translation);

	if (mTarget.isSet) 
	{
		float x1 = GetPosition(0.5f, 0.5f).x;
		float y1 = GetPosition(0.5f, 0.5f).y;

		float x2 = x1 + mDirection.x * mTarget.distance;
		float y2 = y1 + mDirection.y * mTarget.distance;

		Debug::DrawLine(x1, y1, x2, y2, sf::Color::Cyan);

		Debug::DrawCircle(mTarget.position.x, mTarget.position.y, 5.f, sf::Color::Magenta);

		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y, 0.5f, 0.5f);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}

	OnUpdate();
}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}