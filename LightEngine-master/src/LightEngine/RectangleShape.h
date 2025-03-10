#pragma once
#include "Entity.h"

class RectangleShape : public Entity
{
	float mHeight;
	float mWidth;

public:
	RectangleShape(float height, float width) { mHeight = height; mWidth = width; }
	float GetHeight() { return mHeight; }
	float GetWidth() { return mWidth; }
	void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f) override;
};

