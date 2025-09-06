#pragma once

#include "StatusComponent.h"

class CPowerUpDataManager;

class CPlayerStatusComponent : public CStatusComponent
{
public:
	CPlayerStatusComponent();
	virtual ~CPlayerStatusComponent();

private:
	// 파워업 관련
	float mPowerUpModifiers[(int)EPowerUpType::MAX] = {};
	
	// 레벨 및 경험치 관련
	float mExpToLevelUp = 12.0f;
	int mLevelUpNotifyCount = 0;

	// 기본 스탯
	float mBasePickupRange = 0.0f;
	float mBaseGrowthExp   = 0.0f;

private:
	virtual bool Init()    final;
	virtual void Release() final;

public:
	float GetStatModifier(EPowerUpType type) { return mPowerUpModifiers[(int)type]; }

	float GetBasePickupRange() const { return mBasePickupRange; }
	float GetBaseGrowthExp()   const { return mBaseGrowthExp; }

	int PopLevelUpNotify();
	void AddExp(float exp);
};