#pragma once

#include "../../Core/GameInfo.h"

class CGameDataManager
{
	friend class CGameManager;

private:
	CGameDataManager();
	~CGameDataManager();

private:
	class CInfoManager* mInfoManager;

	static CGameDataManager* mInst;

private:
	bool Init();

public:
	CInfoManager* GetInfoManager()   const { return mInfoManager; }


public:
	static CGameDataManager* GetInst()
	{
		if (!mInst)
			mInst = new CGameDataManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};