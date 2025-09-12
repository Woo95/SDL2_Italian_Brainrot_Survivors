#pragma once

#include "Component.h"
#include "../../Core/Utils/GameDataUtils.h"

class CItemDataManager;

class CPlayerStatusComponent : public CComponent
{
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
	int mLevel = 1;
	float mHP = 0.0f;
	float mMaxHP = 0.0f;
	float mExp = 0.0f;
	float mExpToLevelUp = 12.0f;
	int mKillCount = 0;

private:
	virtual bool Init()    final;
	virtual void Release() final;

public:
	void AddExp(float exp);
	void AddHP(float hp);

	float GetStatModifier(EPowerUpType type) const { return mPowerUpModifiers[(int)type]; }
	int GetMenuPowerUpLvl(EPowerUpType type) const { return mMenuPowerUps[(int)type]; }

	float GetBaseAttack()      const { return mBaseAttack; }
	float GetBaseDefense()     const { return mBaseDefense; }
	float GetBaseMaxHP()       const { return mBaseMaxHP; }
	float GetBaseAttackSpeed() const { return mBaseAttackSpeed; }
	float GetBaseMoveSpeed()   const { return mBaseMoveSpeed; }
	float GetBasePickupRange() const { return mBasePickupRange; }
	float GetBaseGrowthExp()   const { return mBaseGrowthExp; }

	int GetLevel()     const { return mLevel; }
	float GetHP()      const { return mHP; }
	float GetExp()     const { return mExp; }
	int GetKillCount() const { return mKillCount; }
};