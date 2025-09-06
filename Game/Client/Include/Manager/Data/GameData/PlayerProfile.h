#pragma once

#include "../../../Core/Utils/GameDataUtils.h"

// CPlayerProfile는 모든 씬에서 사용되는 플레이어의 영구 데이터를 관리하는 클래스
class CPlayerProfile
{
	friend class CGameDataManager;
	friend class CDataLoader;

private:
	CPlayerProfile();
	~CPlayerProfile();

private:
	ECharacterType mType = ECharacterType::NONE;
	int mMenuPowerUps[(int)EPowerUpType::MAX] = {};
	int mMoneyBalance = 5900;

public:
	// 캐릭터 관련 //
	const std::string& GetName() const;
	ECharacterType GetType() const
	{
		return mType;
	}
	void SetType(ECharacterType type)
	{ 
		mType = type;
	}

	// 파워 업 관련 //
	int GetMenuPowerUpLvl(EPowerUpType type) const
	{
		return mMenuPowerUps[(int)type];
	}
	bool PurchaseMenuPowerUp(EPowerUpType type);
	bool RefundAllMenuPowerUp();

	// 돈 관련 //
	int GetBalance() const
	{
		return mMoneyBalance;
	}
	void AddBalance(int amount)
	{ 
		mMoneyBalance += amount; 
	}
};