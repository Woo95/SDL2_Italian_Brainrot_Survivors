#pragma once

#include "Object.h"

class CEnemyStatusComponent;
class CSpriteComponent;
class CChaseComponent;
class CRigidbody;
class CCollider;
class CPlayer;

class CEnemy abstract : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	CPlayer* mPlayer = nullptr;

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

	void TakeDamage(float amount);

protected:
	bool Chance(float probability)
	{
		return ((float)std::rand() / RAND_MAX) < probability;
	}
	void DropGem();

private:
	// Collision Events //
	void OnCollisionEnter(CCollider* self, CCollider* other);
	void OnCollisionExit(CCollider* self, CCollider* other);
};