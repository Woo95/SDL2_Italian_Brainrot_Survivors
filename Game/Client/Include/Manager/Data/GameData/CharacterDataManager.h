#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CCharacterDataManager
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CCharacterDataManager() = default;
	~CCharacterDataManager() = default;

private:
	FCharacterData mData[(int)ECharacterType::MAX];

public:
	const FCharacterData& GetCharacterData(ECharacterType type)
	{
		return mData[(int)type];
	}
};