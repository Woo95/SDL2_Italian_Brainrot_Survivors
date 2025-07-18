#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Core/Utils/StatUtils.h"

struct FCharacterData
{
	std::string lastName;
	std::string firstName;
	std::string description1;
	std::string description2;
	std::string startingWeapon;
	FStat stat;
};

class CCharacterDataManager
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CCharacterDataManager() = default;
	~CCharacterDataManager() = default;

private:
	std::unordered_map<std::string, FCharacterData> mDatas;

public:
	const FCharacterData& GetCharacterData(const std::string& key)
	{
		std::unordered_map<std::string, FCharacterData>::iterator iter = mDatas.find(key);

		assert(iter != mDatas.end());

		return iter->second;
	}
};