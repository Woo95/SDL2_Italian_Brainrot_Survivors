#include "GameDataManager.h"
#include "InfoManager.h"

CGameDataManager* CGameDataManager::mInst = nullptr;

CGameDataManager::CGameDataManager() :
	mInfoManager(nullptr)
{
}

CGameDataManager::~CGameDataManager()
{
	SAFE_DELETE(mInfoManager);
}

bool CGameDataManager::Init()
{
	mInfoManager = new CInfoManager;

	return true;
}