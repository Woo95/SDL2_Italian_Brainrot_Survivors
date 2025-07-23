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
	std::unordered_map<std::string, FPowerUpData> mDatas;

public:
	const FPowerUpData& GetPowerUpData(const std::string& key)
	{
		std::unordered_map<std::string, FPowerUpData>::iterator iter = mDatas.find(key);

		assert(iter != mDatas.end());

		return iter->second;
	}
};