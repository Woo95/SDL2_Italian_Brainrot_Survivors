#pragma once

#include "Component.h"
#include "../../Core/Utils/InventoryUtils.h"

class CWeapon;

class CInventoryComponent : public CComponent
{
public:
	CInventoryComponent();
	virtual ~CInventoryComponent();

private:
	int mPowerUps[(int)EPowerUpType::MAX];
	int mPowerUpCount;

	CWeapon* mWeapons[CONST_MAX_WEAPON_SLOT];
	int mWeaponCount;

private:
	virtual void Release() final;

public:
	bool AddPowerUp(EPowerUpType type);
	bool AddWeapon(CWeapon* weapon);

	int& GetPowerUpFromInventory(EPowerUpType type) { return mPowerUps[(int)type]; }
	int GetPowerUpLevel(EPowerUpType type) const { return mPowerUps[(int)type]; }

	CWeapon* GetWeaponFromInventory(EWeaponType type) const;
	int GetWeaponLevel(EWeaponType type) const;

	bool HasEmptySlot(EItemCategory category) const
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