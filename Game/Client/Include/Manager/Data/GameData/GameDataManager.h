#pragma once

#include "../../../Core/GameInfo.h"

class CGameDataManager
{
	friend class CEngine;

private:
	CGameDataManager() = delete;
	CGameDataManager(void* memoryBlock);
	~CGameDataManager();

private:
	static CGameDataManager* mInst;

	class CPlayerProfile*        mPlayerProfile;
	class CCharacterDataManager* mCharacterDataManager;
	class CItemDataManager*      mItemDataManager;
	class CMobDataManager*       mMobDataManager;

public:
	CPlayerProfile*        GetPlayerProfile()        const { return mPlayerProfile; }
	CCharacterDataManager* GetCharacterDataManager() const { return mCharacterDataManager; }
	CItemDataManager*      GetItemDataManager()      const { return mItemDataManager; }
	CMobDataManager*       GetMobDataManager()       const { return mMobDataManager;}

private:
	template <typename T>
	T* PlacementNew(void*& memoryBlock)
	{
		T* ptr = new (memoryBlock) T;
		memoryBlock = (char*)memoryBlock + sizeof(T);

		return ptr;
	}
	template <typename T>
	void PlacementDelete(T*& ptr)
	{
		ptr->~T();
		ptr = nullptr;
	}

public:
	static CGameDataManager* GetInst();
private:
	static void DestroyInst();
};