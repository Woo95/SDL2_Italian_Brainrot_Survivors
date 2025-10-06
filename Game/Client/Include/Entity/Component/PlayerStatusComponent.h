#pragma once

#include "Component.h"
#include "../../Core/Utils/GameDataUtils.h"

class CItemDataManager;

class CPlayerStatusComponent : public CComponent
{
	friend class CPlayer;

public:
	CPlayerStatusComponent();
	virtual ~CPlayerStatusComponent();

private:
	// 초기 파워업 데이터 (메뉴 + 보정치)
	int mMenuPowerUps[(int)EPowerUpType::MAX] = {};
	float mPowerUpModifiers[(int)EPowerUpType::MAX] = {};

	// 초기 스탯
	float mBaseAttack      = 0.0f;
	float mBaseDefense     = 0.0f;
	float mBaseMaxHP       = 0.0f;
	float mBaseAttackSpeed = 0.0f;
	float mBaseMoveSpeed   = 0.0f;
	float mBasePickupRange = 0.0f;
	float mBaseGrowthExp   = 0.0f;

	// 현재 상태
	int mLevel   = 1;
	float mHP    = 0.0f;
	float mMaxHP = 0.0f;
	float mExp   = 0.0f;
	float mExpToLevelUp = 12.0f;
	int mKillCount  = 0;
	int mGoldEarned = 0;
	int mPendingLevelUps = 0;

private:
	virtual void Release() final;

public:
	int GetLevel()      const { return mLevel; }
	float GetHP()       const { return mHP; }
	float GetExp()      const { return mExp; }
	int GetKillCount()  const { return mKillCount; }
	int GetGoldEarned() const { return mGoldEarned; }
	int GetPendingLevelUps() const { return mPendingLevelUps; }

public:
	void SetStatus(ECharacterType type);
	void ProcessPendingLevelUp(float delayTime);

private:
	void AddHP(float hp);
	void AddExp(float exp);
	void AddKill()
	{
		mKillCount++;
	}
	void AddGold(int money)
	{
		mGoldEarned += money;
	}

	float GetStatModifier(EPowerUpType type) const { return mPowerUpModifiers[(int)type]; }
	int GetMenuPowerUpLvl(EPowerUpType type) const { return mMenuPowerUps[(int)type]; }

	float GetBaseAttack()      const { return mBaseAttack; }
	float GetBaseDefense()     const { return mBaseDefense; }
	float GetBaseMaxHP()       const { return mBaseMaxHP; }
	float GetBaseAttackSpeed() const { return mBaseAttackSpeed; }
	float GetBaseMoveSpeed()   const { return mBaseMoveSpeed; }
	float GetBasePickupRange() const { return mBasePickupRange; }
	float GetBaseGrowthExp()   const { return mBaseGrowthExp; }
};