#pragma once

#include "Object.h"
#include "../../Core/Vector2D.h"
#include "../../Core/Utils/GameDataUtils.h"

class CSoundManager;

class CPlayerStatusComponent;
class CInventoryComponent;
class CMovementComponent;
class CSpriteComponent;
class CInputComponent;
class CVFXComponent;
class CRigidbody;
class CCollider;

class CPlayer abstract : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

protected:
	CPlayerStatusComponent* mStatus = nullptr;
	CInventoryComponent* mInventory = nullptr;
	CMovementComponent* mMovement = nullptr;
	CSpriteComponent* mSprite = nullptr;
	CInputComponent* mInput = nullptr;
	CVFXComponent* mHitVfx = nullptr;
	CRigidbody* mRigidbody = nullptr;
	CCollider* mPickUpZone = nullptr;
	CCollider* mHitbox = nullptr;

	float mHealTimer = 0.0f;
	const float CONST_HEAL_TIMER = 1.0f;

protected:
	virtual bool Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() = 0;

	virtual void OnMoveDirChanged(const FVector2D& dir) = 0;

public:
	void TakeDamage(float amount);
	void Heal(float amount);
	void AddExp(float exp);
	void AddKill();
	void AddGold(int money);
	void AddPowerUp(EPowerUpType type);
	void AddWeapon(EWeaponType type);
	void AddConsumable(EConsumableType type);

	CPlayerStatusComponent* GetStatus() const { return mStatus; }
	CInventoryComponent* GetInventory() const { return mInventory; }
	CMovementComponent* GetMovement() const { return mMovement; }
	CSpriteComponent* GetSprite() const { return mSprite; }
	CCollider* GetPickUpZone() const { return mPickUpZone; }
	CCollider* GetHitbox() const { return mHitbox; }

	float GetAttack() const;
	float GetDefense() const;
	float GetMaxHP() const;
	float GetRecoveryHP() const;
	float GetMoveSpeed() const;
	float GetPickupRange() const;
	float GetGrowthExp() const;
	float GetGreed() const;

private:
	void MoveDir(const FVector2D& dir);
};