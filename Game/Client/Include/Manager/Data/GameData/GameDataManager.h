#pragma once

#include "../../../Core/GameInfo.h"
#include "CharacterDataManager.h"
#include "PlayerData.h"

class CGameDataManager
{
	friend class CGameManager;

private:
	CGameDataManager() = default;
	~CGameDataManager() = default;

private:
	static CGameDataManager* mInst;

	CPlayerData mPlayerData;

	CCharacterDataManager mCharacterDataManager;

public:
	CPlayerData& GetPlayerData() { return mPlayerData; }

	CCharacterDataManager& GetCharacterDataManager() { return mCharacterDataManager; }

public:
	static CGameDataManager* GetInst()
	{
		if (!mInst)
			mInst = new CGameDataManager;
		return mInst;
	}
private:
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};