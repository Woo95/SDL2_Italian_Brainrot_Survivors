#pragma once

#include "../../../Core/GameInfo.h"

class CGameDataManager
{
	friend class CGameManager;

private:
	CGameDataManager() = delete;
	CGameDataManager(void* memoryBlock);
	~CGameDataManager();

private:
	static CGameDataManager* mInst;

	class CPlayerData*           mPlayerData;
	class CCharacterDataManager* mCharacterDataManager;
	class CPowerUpDataManager*   mPowerUpDataManager;

public:
	CPlayerData*           GetPlayerData()           const { return mPlayerData; }
	CCharacterDataManager* GetCharacterDataManager() const { return mCharacterDataManager; }
	CPowerUpDataManager*   GetPowerUpDataManager()   const { return mPowerUpDataManager; }

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