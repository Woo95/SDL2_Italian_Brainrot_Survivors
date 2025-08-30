#pragma once

class CPlayTimer
{
public:
	CPlayTimer()  = default;
	~CPlayTimer() = default;

private:
	float mTime = 0.0f;

public:
	float Update(float deltaTime)
	{
		mTime -= deltaTime;
		return mTime;
	}

	float GetTime() const { return mTime; }
	void SetTime(float startTime)
	{
		mTime = startTime;
	}
};