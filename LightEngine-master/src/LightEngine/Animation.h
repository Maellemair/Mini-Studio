#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "json.hpp"

class Texture;

enum Direction
{
	Up,
	Down,
	Left,
	Right
};

class Animation
{

	sf::Shape* mShapeAnim;
	sf::Vector2f mPos;
	sf::Vector2f mSizeFrame;
	float mSizeLimited;
	int mCurrentIndex = 0;
	int mNbrFrame;
	bool mLoop;
	int mNbrLoop;
	float mDuration;
	float mDurationProgress = mDuration;
public:
	void ResetNBrLoop();
	void SetShape(sf::Shape* pShape, sf::Vector2f pPos, const int nbrFrame, const float pDuration, bool pLoop);
	bool Update(float dt);
};

