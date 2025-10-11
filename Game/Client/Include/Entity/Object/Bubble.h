#pragma once

#include "Object.h"

class CMovementComponent;

class CBubble : public CObject
{
public:
	CBubble();
	virtual ~CBubble();

private:
	CMovementComponent* mMovement = nullptr;
	FVector2D mMoveDir = FVector2D::ZERO;

	float mDamage = 0.0f;
	float mDestroyTime = 3.0f;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	void SetMoveDir(FVector2D dir)
	{
		mMoveDir = dir;
	}
	void SetDamage(float damage)
	{
		mDamage = damage;
	}
};