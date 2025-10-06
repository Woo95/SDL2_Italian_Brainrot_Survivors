#pragma once

#include "Object.h"
#include "../../Core/Vector2D.h"
#include "../../Core/Utils/GameDataUtils.h"

class CPlayerStatusComponent;
class CInventoryComponent;
class CMovementComponent;
class CSpriteComponent;
class CInputComponent;
class CRigidbody;

class CWeaponComponent;

class CPlayer abstract : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

protected:
	CPlayerStatusComponent* mStatus;
	CInventoryComponent* mInventory;
	CMovementComponent* mMovement;
	CSpriteComponent* mSprite;
	CInputComponent* mInput;
	CRigidbody* mRigidbody;

public:
	virtual bool Init() override;

private:
	virtual void Release() = 0;
	virtual void OnMoveDirChanged(const FVector2D& dir) = 0;

public:
	CPlayerStatusComponent* GetStatus() const { return mStatus; }
	CInventoryComponent* GetInventory() const { return mInventory; }
	CMovementComponent* GetMovement() const { return mMovement; }
	CSpriteComponent* GetSprite() const { return mSprite; }

	void TakeDamage(float amount);
	void Heal(float amount);
	void AddExp(float exp);
	void AddKill();
	void AddGold(int money);
	void AddPowerUp(EPowerUpType type);
	void AddWeapon(EWeaponType type);
	void AddConsumable(EConsumableType type);

public:
	float GetAttack()      const;
	float GetDefense()     const;
	float GetMaxHP()       const;
	float GetRecoveryHP()  const;
	float GetAttackSpeed() const;
	float GetMoveSpeed()   const;
	float GetPickupRange() const;
	float GetGrwothExp()   const;

private:
	void BindInput();
	void MoveDir(const FVector2D& dir);
};