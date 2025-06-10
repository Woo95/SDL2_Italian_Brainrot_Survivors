#pragma once

#include "../Core/GameInfo.h"

class CDataManager
{
    friend class CGameManager;

private:
    CDataManager();
    ~CDataManager();

private:
	static CDataManager* mInst;

private:
    bool Init();

    std::vector<std::string> Split(const std::string& line, char delimiter);

    void LoadAllEntityFrameData();
    void LoadAllEntityAnimationData();
    void LoadAllWidgetData();

    void LoadAllCharacterInfo();

public:
	static CDataManager* GetInst()
	{
		if (!mInst)
			mInst = new CDataManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};