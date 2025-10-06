#pragma once

#include "Component.h"
#include "../../Core/Utils/InventoryUtils.h"

class CWeaponComponent;

class CInventoryComponent : public CComponent
{
public:
	CInventoryComponent();
	virtual ~CInventoryComponent();

private:
	FPowerUp mPowerUps[CONST_MAX_POWERUP_SLOT] = {};
	int mPowerUpCount = 0;

	FWeapon mWeapons[CONST_MAX_POWERUP_SLOT] = {};
	int mWeaponCount = 0;

private:
	virtual void Release() final;

public:
	void AddPowerUp(EPowerUpType type);
	void AddWeapon(EWeaponType type, CWeaponComponent* weapon);

	FPowerUp* GetPowerUp(EPowerUpType type);
	FWeapon* GetWeapon(EWeaponType type);

	int GetPowerUpLevel(EPowerUpType type);
	int GetWeaponLevel(EWeaponType type);

	bool HasEmptySlot(EItemCategory category)
	{
		bool hasEmpty = false;
		switch (category)
		{
		case EItemCategory::POWERUP:
			hasEmpty = mPowerUpCount < CONST_MAX_POWERUP_SLOT;
			break;
		case EItemCategory::WEAPON:
			hasEmpty = mWeaponCount < CONST_MAX_WEAPON_SLOT;
			break;
		}
		return hasEmpty;
	}
};