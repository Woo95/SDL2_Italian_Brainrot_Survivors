#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CItemDataManager
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CItemDataManager() = default;
	~CItemDataManager() = default;

private:
	FPowerUpData    mPowerUpData[(int)EPowerUpType::MAX];
	FWeaponData     mWeaponData[(int)EWeaponType::MAX];
	FConsumableData mConsumableData[(int)EConsumableType::MAX];


public:
	const FPowerUpData& GetPowerUpData(EPowerUpType type) const
	{ 
		return mPowerUpData[(int)type];
	}
	const FWeaponData& GetWeaponData(EWeaponType type) const
	{
		return mWeaponData[(int)type];
	}
	const FConsumableData& GetConsumableData(EConsumableType type) const
	{
		return mConsumableData[(int)type];
	}
};