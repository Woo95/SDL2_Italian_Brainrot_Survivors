#pragma once

#include "Component.h"

class CObject;

class CChaseComponent : public CComponent
{
public:
	CChaseComponent();
	virtual ~CChaseComponent();

private:
	float mSpeed;

	FVector2D mFacingDir;

	CTransform* mSelf;
	CTransform* mTarget;
	
private:
	virtual bool Init() final;
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	float GetSpeed() const { return mSpeed; }
	const FVector2D& GetFacingDir() const { return mFacingDir; }

	void SetTarget(CTransform* target)
	{
		mTarget = target;
	}
};