#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf 
{
	class Shape;
    class Color;
}

enum CollisionFace {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	None,
};


struct AABBCollider
{
	float xMin, yMin;
	float xMax, yMax;
	float xSize, ySize;
};

class Scene;
class Player;

class Entity
{
    struct Target 
    {
		sf::Vector2i position;
        float distance;
		bool isSet;
    };

protected:
	CollisionFace state = None;
	AABBCollider* mBoxCollider;
    sf::RectangleShape* mShape;
    sf::Vector2f mDirection;
	Target mTarget;
    float mSpeed = 0.f;
    bool mToDestroy = false;
    int mTag = -1;
	bool mRigidBody = false;

public:
	bool GoToDirection(int x, int y, float speed = -1.f);
    bool GoToPosition(int x, int y, float speed = -1.f);
    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
	void SetCollider(float posX, float posY, float height, float width);
	void SetDirection(float x, float y, float speed = -1.f);
	sf::Vector2f GetDirection() { return mDirection; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetTag(int tag) { mTag = tag; }
	void PrintCollider(sf::Color color);
	const int GetTag() { return mTag; }
	void SetStateCollision(CollisionFace pState) { state = pState; }
	CollisionFace GetStateCollision() { return state; }
	
	//float GetRadius() const;
	float GetHeight() const;
	float GetWidth() const;
	void SetRigidBody(bool isRigitBody) { mRigidBody = isRigitBody; }
	bool IsRigidBody() const { return mRigidBody; }

    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Vector2f GetColliderPos(float ratioX = 0.5f, float ratioY = 0.5f) const;
	sf::Vector2f GetColliderSize();
	AABBCollider* GetCollider() { return mBoxCollider; }
	sf::Shape* GetShape() { return mShape; }

	bool IsTag(int tag) const { return mTag == tag; }
	bool IsInside(float x, float y) const;
	bool IsColliding(Entity* other) const;
    void Destroy();
	bool ToDestroy() const { return mToDestroy; }
	
	template<typename T>
	T* GetScene() const;

	template<typename T>
	T* CreateRectangle(float height, float width, const sf::Color& color);

    Scene* GetScene() const;
	float GetDeltaTime() const;

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	
private:
    void Update();
	void InitializeRect(float height, float width, const sf::Color& color);
	void Repulse(Entity* other) { };

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"