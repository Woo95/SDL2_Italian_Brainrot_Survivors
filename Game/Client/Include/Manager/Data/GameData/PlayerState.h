#pragma once

#include "../../../Core/Utils/StatUtils.h"
#include "../../../Core/Utils/GameDataUtils.h"

class CPlayerState
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPlayerState();
	~CPlayerState();

private:
	ECharacterType mSelectedCharacter = ECharacterType::NONE;
	bool mOwnedPowerUp[(int)EPowerUpType::MAX] = {};
	int mMoneyBalance = 5900;

public:
	// 캐릭터 관련 //
	ECharacterType GetSelectedCharacter() const { return mSelectedCharacter; }
	void SetSelectedCharacter(ECharacterType type)
	{ 
		mSelectedCharacter = type;
	}

	// 파워 업 관련 //
	bool IsPowerUpOwned(EPowerUpType type) const { return mOwnedPowerUp[(int)type]; }
	bool PurchasePowerUp(EPowerUpType type);
	bool RefundAllPowerUp();

	// 돈 관련 //
	int GetBalance() const { return mMoneyBalance; }
	void AddBalance(int amount)
	{ 
		mMoneyBalance += amount; 
	}
};