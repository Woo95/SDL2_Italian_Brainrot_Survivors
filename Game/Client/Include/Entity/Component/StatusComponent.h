#pragma once

#include "Component.h"
#include "../../Core/Utils/GameDataUtils.h"

class CStatusComponent abstract : public CComponent
{
public:
	CStatusComponent() = default;
	virtual ~CStatusComponent() = default;

protected:
	// 현재 상태
	int mLevel = 1;
	float mExp = 0.0f;
	float mHP  = 0.0f;

	// 기본 스탯
	float mBaseAttack      = 0.0f;
	float mBaseDefense     = 0.0f;
	float mBaseMaxHP       = 0.0f;
	float mBaseAttackSpeed = 0.0f;
	float mBaseMoveSpeed   = 0.0f;

private:
	virtual void Release() = 0;

public:
	int GetLevel() const { return mLevel; }
	float GetExp() const { return mExp; }
	float GetHP()  const { return mHP; }

	float GetBaseAttack()      const { return mBaseAttack; }
	float GetBaseDefense()     const { return mBaseDefense; }
	float GetBaseMaxHP()       const { return mBaseMaxHP; }
	float GetBaseAttackSpeed() const { return mBaseAttackSpeed; }
	float GetBaseMoveSpeed()   const { return mBaseMoveSpeed; }
};