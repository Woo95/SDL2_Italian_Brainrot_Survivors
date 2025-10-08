#pragma once

#include "Object.h"

class CSpriteComponent;
class CCircleCollider;

class CBanana : public CObject
{
public:
	CBanana();
	virtual ~CBanana();

private:
	CSpriteComponent* mSprite = nullptr;
	CCircleCollider* mCollider = nullptr;

	FVector2D mScale = FVector2D(75.0f, 75.0f);

public:
	virtual bool Init() final;

private:
	virtual void Release() final;

public:
	const FVector2D& GetScale() { return mScale; }
	void SetScale(const FVector2D& scale);
};