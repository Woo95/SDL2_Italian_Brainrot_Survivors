#pragma once

#include "Object.h"

class CChaseComponent;
class CCollider;

class CGem : public CObject
{
public:
	CGem();
	virtual ~CGem();

private:
	CChaseComponent* mChase = nullptr;

	float mExp = 0.0f;

public:
	virtual bool Init() final;

private:
	virtual void Release() final;

public:
	float GetExp() const { return mExp; }
	void SetExp(float exp)
	{
		mExp = exp;
	}

private:
	void OnCollisionEnter(CCollider* self, CCollider* other);
};