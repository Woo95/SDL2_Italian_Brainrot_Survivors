#pragma once

#include "Object.h"

class CCamera;
class CSpriteComponent;
class CCollider;

// ScrollEnvironmentObject
class CScrollEnvObj : public CObject
{
public:
	CScrollEnvObj();
	virtual ~CScrollEnvObj();

private:
	CCamera* mCamera;

	FVector2D mMapScale;
	float mSnapThreshold;

	CSpriteComponent* mSprite;
	CCollider* mCollider;

public:
	virtual bool Init() final;
	virtual void Update(float deltaTime) final;

private:
	virtual void Release() final;

public:
	void SetMapScale(const FVector2D& mapScale)
	{
		mMapScale = mapScale;

		mSnapThreshold = mMapScale.Length() * 0.5f;
	}
	void SetMapScale(float x, float y)
	{
		mMapScale = FVector2D(x, y);

		mSnapThreshold = mMapScale.Length() * 0.5f;
	}
};