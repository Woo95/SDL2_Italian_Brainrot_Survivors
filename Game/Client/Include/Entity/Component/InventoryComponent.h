#pragma once

#include "Component.h"
#include "../../Core/Utils/InventoryUtils.h"

class CInventoryComponent : public CComponent
{
public:
	CInventoryComponent();
	virtual ~CInventoryComponent();

private:
	int mPowerUps[(int)EPowerUpType::MAX];
	int mPowerUpCount;

	int mWeapons[(int)EWeaponType::MAX];
	int mWeaponCount;

private:
	virtual bool Init()    final;
	virtual void Release() final;

public:
	bool AddPowerUp(EPowerUpType type);
	bool AddWeapon(EWeaponType type);

	int GetPowerUpLevel(EPowerUpType type) const { return mPowerUps[(int)type]; }
	int GetWeaponLevel(EWeaponType type) const { return mWeapons[(int)type]; }

	bool HasEmptySlot(EItemCategory category) const
	{
		if (category == EItemCategory::POWERUP)
		{
			return mPowerUpCount < CONST_MAX_POWERUP_SLOT;
		}
		else
		{
			return mWeaponCount < CONST_MAX_WEAPON_SLOT;
		}
	}
	bool HasItem(EItemCategory category, int type) const
	{
		if (category == EItemCategory::POWERUP)
			return mPowerUps[type] > 0;
		else if (category == EItemCategory::WEAPON)
			return mWeapons[type] > 0;

		return false;
	}
};