#pragma once

#include "Object.h"

class CSpriteComponent;
class CCircleCollider;
class CCollider;

class CBanana : public CObject
{
public:
	CBanana();
	virtual ~CBanana();

private:
	CSpriteComponent* mSprite = nullptr;
	CCircleCollider* mCollider = nullptr;
	FVector2D mScale = FVector2D(90.0f, 90.0f);

	float mDamage = 0.0f;

public:
	virtual bool Init() final;

private:
	virtual void Release() final;

public:
	const FVector2D& GetScale() { return mScale; }

	void SetScale(const FVector2D& scale);
	void SetDamage(float damage)
	{
		mDamage = damage;
	}

private:
	void OnCollisionStay(CCollider* self, CCollider* other);
};