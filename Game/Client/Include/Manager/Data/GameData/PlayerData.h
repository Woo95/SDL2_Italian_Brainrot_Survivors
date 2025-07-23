#pragma once

#include "../../../Core/Utils/StatUtils.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CPlayerData
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPlayerData() = default;
	~CPlayerData() = default;

private:
	float mMoneyBalance = 0;

	ECharacterType mSelectedCharacter = ECharacterType::NONE;

public:
	ECharacterType GetSelectedCharacter() const { return mSelectedCharacter; }

	void SetSelectedCharacter(ECharacterType type)
	{
		mSelectedCharacter = type;
	}
};