#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CPowerUpDataManager
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPowerUpDataManager() = default;
	~CPowerUpDataManager() = default;

private:
	FPowerUpData mData[(int)EPowerUpType::MAX];

public:
	const FPowerUpData& GetPowerUpData(EPowerUpType type)
	{
		return mData[(int)type];
	}
};