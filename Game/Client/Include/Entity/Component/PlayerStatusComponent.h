#pragma once

#include "StatusComponent.h"
#include "../../Core/Utils/GameDataTypeUtils.h"

class CPowerUpDataManager;

class CPlayerStatusComponent : public CStatusComponent
{
public:
	CPlayerStatusComponent();
	virtual ~CPlayerStatusComponent();

private:
	CPowerUpDataManager* mPowerUpDataManager;

	// 파워업 관련
	int mPowerUpLevel[(int)EPowerUpType::MAX];
	
	// 레벨 및 경험치 관련
	float mExpToLevelUp;
	int mLevelUpNotifyCount;

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

	int PopLevelUpNotify();
	void AddExp(float exp);
};