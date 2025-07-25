#pragma once

#include "../../../Core/Utils/StatUtils.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CPlayerState
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPlayerState() = default;
	~CPlayerState() = default;

private:
	ECharacterType mSelectedCharacter = ECharacterType::NONE;

	int mMoneyBalance = 0;

public:
	ECharacterType GetSelectedCharacter() const { return mSelectedCharacter; }

	void SetSelectedCharacter(ECharacterType type)
	{
		mSelectedCharacter = type;
	}
};