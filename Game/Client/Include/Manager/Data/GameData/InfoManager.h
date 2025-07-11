#pragma once

#include "../../../Core/GameInfo.h"

struct FCharacterInfo
{
	std::string name;
	std::string description1;
	std::string description2;
	std::string character;
	std::string weapon;
};

struct FItemInfo
{
	std::string name;
	std::string description1;
	std::string description2;
	std::string item;
};

class CInfoManager
{
	friend class CGameDataManager;
    friend class CDataLoader;

private:
	CInfoManager() = default;
	~CInfoManager() = default;

private:
	std::unordered_map<std::string, FCharacterInfo> mCharacterInfo;
	std::unordered_map<std::string, FItemInfo> mItemInfo;

public:
	const FCharacterInfo* const GetCharacterInfo(const std::string& key)
	{
		std::unordered_map<std::string, FCharacterInfo>::iterator iter = mCharacterInfo.find(key);

		if (iter == mCharacterInfo.end())
			return nullptr;

		return &iter->second;
	}

	const FItemInfo* const GetItemInfo(const std::string& key)
	{
		std::unordered_map<std::string, FItemInfo>::iterator iter = mItemInfo.find(key);

		if (iter == mItemInfo.end())
			return nullptr;

		return &iter->second;
	}
};