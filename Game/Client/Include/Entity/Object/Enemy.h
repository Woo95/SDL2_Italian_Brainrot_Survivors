#pragma once

#include "Object.h"

class CEnemyStatusComponent;
class CSpriteComponent;
class CChaseComponent;
class CVFXComponent;
class CRigidbody;
class CCollider;
class CPlayer;

class CEnemy abstract : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	CPlayer* mTarget = nullptr;

	CEnemyStatusComponent* mStatus = nullptr;
	CSpriteComponent* mSprite = nullptr;
	CChaseComponent* mChase = nullptr;
	CVFXComponent* mHitVfx = nullptr;
	CRigidbody* mRigidbody = nullptr;
	CCollider* mHitbox = nullptr;

	bool mIsInvincible = false;
	float mInvincibleTimer = 0.0f;
	const float CONST_INVINCIBLE_TIMER = 0.5f;

	enum EGem { NONE, BLUE, RED };
	EGem mGemType = EGem::NONE;
	float mGemSpawnRate = 0.0f;

protected:
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() = 0;

public:
	CChaseComponent* GetChase() const { return mChase; }

	void TakeDamage(float amount, bool useInvincibility = false);

private:
	void OnCollisionEnter(CCollider* self, CCollider* other);
	void OnCollisionStay(CCollider* self, CCollider* other);
	void OnCollisionExit(CCollider* self, CCollider* other);

	bool Chance(float probability)
	{
		return ((float)std::rand() / RAND_MAX) < probability;
	}
};