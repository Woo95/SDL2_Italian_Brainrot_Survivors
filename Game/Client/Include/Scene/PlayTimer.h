#pragma once

class CPlayTimer
{
public:
	CPlayTimer();
	~CPlayTimer();

private:
	float mTime;

public:
	float Update(float deltaTime);

	float GetTime() const { return mTime; }
	void SetTime(float startTime)
	{
		mTime = startTime;
	}
};