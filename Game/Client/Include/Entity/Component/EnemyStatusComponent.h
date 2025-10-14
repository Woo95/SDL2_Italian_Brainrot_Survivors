#pragma once

#include "Component.h"
#include "../../Core/Utils/GameDataUtils.h"

class CItemDataManager;

class CEnemyStatusComponent : public CComponent
{
public:
	CEnemyStatusComponent();
	virtual ~CEnemyStatusComponent();

private:
	// 현재 상태
	float mHP        = 0.0f;
	float mAttack    = 0.0f;
	float mMoveSpeed = 0.0f;
	float mExp       = 0.0f;
	int   mGold      = 0;

private:
	virtual void Release() final;

public:
	void AddHP(float hp)
	{
		mHP += hp;
	}

	float GetHP()        const { return mHP; }
	float GetAttack()    const { return mAttack; }
	float GetMoveSpeed() const { return mMoveSpeed; }
	float GetExp()       const { return mExp; }
	int   GetGold()      const { return mGold; }

	void SetStatus(ERegularMobType type);
	void SetStatus(ESubBossMobType type);
};