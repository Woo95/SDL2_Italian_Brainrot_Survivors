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
	CPowerUpDataManager* mPowerUpDataManager;
	int mPowerUpLevel[(int)EPowerUpType::MAX];
	
	// 레벨 및 경험치 관련
	float mExpToLevelUp = 12.0f;
	int mLevelUpNotifyCount = 0;

public:
	virtual bool Init()    final;
	virtual void Release() final;

public:
	float GetAttack()      const;
	float GetDefense()     const;
	float GetMaxHP()       const;
	float GetRecoveryHP()  const;
	float GetAttackSpeed() const;
	float GetMoveSpeed()   const;
	float GetPickupRange() const;
	float GetGrowthExp()   const;

	int PopLevelUpNotify();
	void AddExp(float exp);
};