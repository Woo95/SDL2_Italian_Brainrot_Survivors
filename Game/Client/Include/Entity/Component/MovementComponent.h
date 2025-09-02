#pragma once

#include "Component.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent();

private:
	float mSpeed;

	FVector2D mMoveDir;
	FVector2D mFacingDir;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	const FVector2D& GetFacingDir() const { return mFacingDir; }
	float GetSpeed() const { return mSpeed; }

	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	void AddMoveDir(const FVector2D& direction)
	{
		mMoveDir += direction;
	}

private:
	void Move(float deltaTime);
};