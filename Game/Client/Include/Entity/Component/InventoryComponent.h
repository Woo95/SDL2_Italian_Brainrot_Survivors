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
	virtual bool Init() final;
	virtual void Release() final;

public:
	bool AddPowerUp(EPowerUpType type);
	bool AddWeapon(EWeaponType type);

	int GetPowerUpLevel(EPowerUpType type) const { return mPowerUps[(int)type]; }
	int GetWeaponLevel(EWeaponType type) const { return mWeapons[(int)type]; }
	int GetPowerUpCount() const { return mPowerUpCount; }
	int GetWeaponCount() const { return mWeaponCount; }
};