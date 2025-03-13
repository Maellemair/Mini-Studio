#include "Animation.h"

void Animation::Update(float dt)
{
	mDuration -= dt;
	if (mDuration <= 0)
	{
		mDuration += 100.f;
		mCurrentIndex = (mCurrentIndex + 1) % 4;
	}
}
