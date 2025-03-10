#include "RectangleShape.h"
#include "Utils.h"

void RectangleShape::SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f)
{
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