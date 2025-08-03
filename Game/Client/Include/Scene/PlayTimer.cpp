#include "PlayTimer.h"

CPlayTimer::CPlayTimer()
{
}

CPlayTimer::~CPlayTimer()
{
}

float CPlayTimer::Update(float deltaTime)
{
	mTime -= deltaTime;

	return mTime;
}