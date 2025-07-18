#pragma once

#include "../../../Core/GameInfo.h"
#include "CharacterDataManager.h"

class CGameDataManager
{
	friend class CGameManager;

private:
	CGameDataManager();
	~CGameDataManager();

private:
	static CGameDataManager* mInst;

	CCharacterDataManager mCharacterDataManager;

public:
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