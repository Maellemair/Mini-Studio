#include "Animation.h"


void Animation::ResetNBrLoop()
{
	mNbrLoop = 0;
}

void Animation::SetShape(sf::Shape* pShape, sf::Vector2f pPos, const int nbrFrame, const float pDuration, bool pLoop)
{
	std::ifstream fichier("../../../res/Player.json");
	if (fichier.is_open())
	{
		nlohmann::json data;
		fichier >> data;
		fichier.close();

		mSizeFrame = sf::Vector2f(data["frame_size"]["width"], data["frame_size"]["height"]);
		mDuration = pDuration;
		mNbrFrame = nbrFrame;
		mLoop = pLoop;
		mShapeAnim = new sf::RectangleShape;
		mShapeAnim = pShape;
		mPos = pPos;
	}
	else
	{
		std::cout << "le fichier d'animation n'existe pas !" << std::endl;
		return;
	}
}

bool Animation::Update(float dt)
{
	if (mShapeAnim == nullptr || (mLoop == false && mNbrLoop != 0))
		return true;

	if (mPos.x >= mSizeFrame.x * (mNbrFrame - 1))
	{
		mPos.x = 0;
		mNbrLoop++;
	}

	mDurationProgress -= dt;
	if (mDurationProgress <= 0)
	{
		mDurationProgress = mDuration;
		mPos.x += mSizeFrame.x;
		mShapeAnim->setTextureRect(sf::IntRect(sf::Vector2i(mPos.x, mPos.y), sf::Vector2i(mSizeFrame.x, mSizeFrame.y)));
	}
	return false;
}
