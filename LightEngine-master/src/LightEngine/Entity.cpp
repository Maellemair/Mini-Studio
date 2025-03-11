#include "Entity.h"

#include "GameManager.h"
#include "Utils.h"
#include "Debug.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

void Entity::InitializeCircle(float radius, const sf::Color& color)
{
	mShape = new sf::CircleShape;
	sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape);

	mDirection = sf::Vector2f(0.0f, 0.0f);

	pShape->setOrigin(0.f, 0.f);
	pShape->setRadius(radius);
	pShape->setFillColor(color);
	
	mTarget.isSet = false;

	OnInitialize();
}

void Entity::InitializeRect(float height, float width, const sf::Color& color)
{
	mShape = new sf::RectangleShape;
	sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape);
	
	pShape->setSize(sf::Vector2f(height, width));
	pShape->setOrigin(0.f, 0.f);
	pShape->setFillColor(color);

	mTarget.isSet = false;
	OnInitialize();
}


void Entity::Repulse(Entity* other) 
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);
	
	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);
	float length = std::sqrt(sqrLength);
	
	float overlap = 0;
	if (sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape))
	{
		float radius1 = pShape->getRadius();
		sf::CircleShape* pOther = dynamic_cast<sf::CircleShape*>(other);
		float radius2 = pOther->getRadius();
		overlap = (length - (radius1 + radius2)) * 0.5f;
	}

	sf::Vector2f normal = distance / length;

	sf::Vector2f translation = overlap * normal;

	sf::Vector2f position1 = GetPosition(0.5f, 0.5f) - translation;
	sf::Vector2f position2 = other->GetPosition(0.5f, 0.5f) + translation;

	SetPosition(position1.x, position1.y, 0.5f, 0.5f);
	other->SetPosition(position2.x, position2.y, 0.5f, 0.5f);
}

bool Entity::IsColliding(Entity* other) const
{
	sf::Vector2f distance = GetPosition(0.5f, 0.5f) - other->GetPosition(0.5f, 0.5f);

	float sqrLength = (distance.x * distance.x) + (distance.y * distance.y);

	float sqrRadius = 0;
	if (sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape))
	{
		float radius1 = pShape->getRadius();
		if (sf::CircleShape* pOther = dynamic_cast<sf::CircleShape*>(other))
		{
			float radius2 = pOther->getRadius();
			sqrRadius = (radius1 + radius2) * (radius1 + radius2);
		}
		else if (sf::RectangleShape* pOther = dynamic_cast<sf::RectangleShape*>(other))
		{
			sqrRadius = sqrLength + 10;
		}
		
	}

	return sqrLength < sqrRadius;
}

bool Entity::IsInside(float x, float y) const
{
	sf::Vector2f position = GetPosition(0.5f, 0.5f);

	float dx = x - position.x;
	float dy = y - position.y;
	
	if (sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape))
	{
		float radius = pShape->getRadius();
		return (dx * dx + dy * dy) < (radius * radius);
	}
	else if (sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape))
	{
		float height = pShape->getSize().y;
		float width = pShape->getSize().x;
		return (dx * dx + dy * dy) < ( height * width);
	}
}

void Entity::Destroy()
{
	mToDestroy = true;

	OnDestroy();
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = mShape->getPosition();

	if (sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape))
	{
		float size = pShape->getRadius() * 2;
		position.x += size * ratioX;
		position.y += size * ratioY;
	}
	else if (sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape))
	{
		float height = pShape->getSize().y;
		float width = pShape->getSize().x;
		position.x += width * ratioX;
		position.y += height * ratioY;
	}

	return position;
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
	if (sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape))
	{
		float size = pShape->getRadius() * 2;
		x -= size * ratioX;
		y -= size * ratioY;
	}
	else if (sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape))
	{
		sf::Vector2f size = pShape->getSize();
		x -= size.x / 2;
		y -= size.y / 2;
	}

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

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
	mTarget.isSet = false;
}

float Entity::GetRadius() const
{
	sf::CircleShape* pShape = dynamic_cast<sf::CircleShape*>(mShape); 
	return pShape->getRadius();
}

float Entity::GetHeigth() const
{
	sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape);
	return pShape->getSize().y;
}

float Entity::GetWidth() const
{
	sf::RectangleShape* pShape = dynamic_cast<sf::RectangleShape*>(mShape);
	return pShape->getSize().x;
}

void Entity::Update()
{
	float dt = GetDeltaTime();
	float distance = dt * mSpeed;
	sf::Vector2f translation = distance * mDirection;
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