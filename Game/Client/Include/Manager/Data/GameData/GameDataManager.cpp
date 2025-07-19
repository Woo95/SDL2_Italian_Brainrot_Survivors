#include "GameDataManager.h"
#include "CharacterDataManager.h"
#include "PowerUpDataManager.h"
#include "PlayerData.h"

CGameDataManager* CGameDataManager::mInst = nullptr;

CGameDataManager::CGameDataManager(void* memoryBlock)
{
	mPlayerData           = PlacementNew<CPlayerData>(memoryBlock);
	mCharacterDataManager = PlacementNew<CCharacterDataManager>(memoryBlock);
	mPowerUpDataManager   = PlacementNew<CPowerUpDataManager>(memoryBlock);
}

CGameDataManager::~CGameDataManager()
{
	PlacementDelete<CPlayerData>(mPlayerData);
	PlacementDelete<CCharacterDataManager>(mCharacterDataManager);
	PlacementDelete<CPowerUpDataManager>(mPowerUpDataManager);
}

CGameDataManager* CGameDataManager::GetInst()
{
	if (!mInst)
	{
		const size_t totalSize = sizeof(CGameDataManager) + sizeof(CPlayerData) + sizeof(CCharacterDataManager) +
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