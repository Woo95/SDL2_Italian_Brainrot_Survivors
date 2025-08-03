#pragma once

#include "../../../Core/Utils/StatUtils.h"
#include "../../../Core/Utils/GameDataUtils.h"

// CPlayerState는 모든 씬에서 사용되는 플레이어의 영구 데이터를 관리하는 클래스
class CPlayerState
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPlayerState();
	~CPlayerState();

private:
	ECharacterType mSelectedCharacter = ECharacterType::NONE;
	int mOwnedPowerUp[(int)EPowerUpType::MAX] = {};
	int mMoneyBalance = 5900;

public:
	// 캐릭터 관련 //
	std::string GetSelectedCharacterName() const
	{
		switch (mSelectedCharacter)
		{
		case ECharacterType::TRALALA:
			return "Tralala";
		case ECharacterType::SAHUR:
			return "Sahur";
		case ECharacterType::BANANINI:
			return "Bananini";
		default:
			return "Unknown";
		}
	}
	ECharacterType GetSelectedCharacter() const { return mSelectedCharacter; }
	void SetSelectedCharacter(ECharacterType type)
	{ 
		mSelectedCharacter = type;
	}

	// 파워 업 관련 //
	int  GetOwnedPowerUpCount(EPowerUpType type) const { return mOwnedPowerUp[(int)type]; }
	bool PurchasePowerUp(EPowerUpType type);
	bool RefundAllPowerUp();

	// 돈 관련 //
	int GetBalance() const { return mMoneyBalance; }
	void AddBalance(int amount)
	{ 
		mMoneyBalance += amount; 
	}
};