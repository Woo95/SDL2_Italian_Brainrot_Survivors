#pragma once

#include "Object.h"

class CEnemyStatusComponent;
class CSpriteComponent;
class CChaseComponent;
class CRigidbody;
class CCollider;

class CEnemy abstract : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	CEnemyStatusComponent* mStatus = nullptr;
	CSpriteComponent* mSprite = nullptr;
	CChaseComponent* mChase = nullptr;
	CRigidbody* mRigidbody = nullptr;
	CCollider* mHitbox = nullptr;

	bool mIsDead = false;

protected:
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() = 0;

public:
	CChaseComponent* GetChase() const { return mChase; }

	// Collision Events //
	void OnHit(CCollider* self, CCollider* other);

	void TakeDamage(float amount);

protected:
	bool Chance(float probability)
	{
		return ((float)std::rand() / RAND_MAX) < probability;
	}
	void DropGem();
};