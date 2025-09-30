#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CMobDataManager
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CMobDataManager() = default;
	~CMobDataManager() = default;

private:
	FRegularMobData mRegularMobData[(int)ERegularMobType::MAX];
	FSubBossMobData mSubBossMobData[(int)ESubBossMobType::MAX];

public:
	const FRegularMobData& GetMobData(ERegularMobType type)
	{
		return mRegularMobData[(int)type];
	}
	const FSubBossMobData& GetMobData(ESubBossMobType type)
	{
		return mSubBossMobData[(int)type];
	}
};