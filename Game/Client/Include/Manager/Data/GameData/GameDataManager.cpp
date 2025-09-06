#include "GameDataManager.h"
#include "CharacterDataManager.h"
#include "PowerUpDataManager.h"
#include "PlayerProfile.h"

CGameDataManager* CGameDataManager::mInst = nullptr;

CGameDataManager::CGameDataManager(void* memoryBlock)
{
	mPlayerProfile        = PlacementNew<CPlayerProfile>(memoryBlock);
	mCharacterDataManager = PlacementNew<CCharacterDataManager>(memoryBlock);
	mPowerUpDataManager   = PlacementNew<CPowerUpDataManager>(memoryBlock);
}

CGameDataManager::~CGameDataManager()
{
	PlacementDelete<CPlayerProfile>(mPlayerProfile);
	PlacementDelete<CCharacterDataManager>(mCharacterDataManager);
	PlacementDelete<CPowerUpDataManager>(mPowerUpDataManager);
}

CGameDataManager* CGameDataManager::GetInst()
{
	if (!mInst)
	{
		const size_t totalSize = sizeof(CGameDataManager) + sizeof(CPlayerProfile) + sizeof(CCharacterDataManager) +
			sizeof(CPowerUpDataManager);

		void* memoryBlock = malloc(totalSize);
		mInst = new (memoryBlock) CGameDataManager((char*)memoryBlock + sizeof(CGameDataManager));
	}
	return mInst;
}

void CGameDataManager::DestroyInst()
{
	if (mInst)
	{
		mInst->~CGameDataManager();
		free(mInst);
	}
}