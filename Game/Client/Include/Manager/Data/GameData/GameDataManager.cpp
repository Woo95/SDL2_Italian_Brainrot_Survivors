#include "GameDataManager.h"
#include "PlayerProfile.h"
#include "CharacterDataManager.h"
#include "ItemDataManager.h"
#include "MobDataManager.h"

CGameDataManager* CGameDataManager::mInst = nullptr;

CGameDataManager::CGameDataManager(void* memoryBlock)
{
	mPlayerProfile        = PlacementNew<CPlayerProfile>(memoryBlock);
	mCharacterDataManager = PlacementNew<CCharacterDataManager>(memoryBlock);
	mItemDataManager      = PlacementNew<CItemDataManager>(memoryBlock);
	mMobDataManager       = PlacementNew<CMobDataManager>(memoryBlock);
}

CGameDataManager::~CGameDataManager()
{
	PlacementDelete<CPlayerProfile>(mPlayerProfile);
	PlacementDelete<CCharacterDataManager>(mCharacterDataManager);
	PlacementDelete<CItemDataManager>(mItemDataManager);
	PlacementDelete<CMobDataManager>(mMobDataManager);
}

CGameDataManager* CGameDataManager::GetInst()
{
	if (!mInst)
	{
		const size_t totalSize = sizeof(CGameDataManager) + sizeof(CPlayerProfile) + 
			sizeof(CCharacterDataManager) + sizeof(CItemDataManager) + sizeof(CMobDataManager);

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