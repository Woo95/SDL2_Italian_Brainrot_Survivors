#pragma once

#include "Component.h"

class CStatusComponent abstract : public CComponent
{
public:
	CStatusComponent() = default;
	virtual ~CStatusComponent() = default;

protected:
	// 현재 상태
	int mLevel;
	float mExp;
	float mHP;

	// 기본 스탯 (파워업 적용 전)
	float mRawAttack;
	float mRawDefense;
	float mRawMaxHP;
	float mRawAttackSpeed;
	float mRawMoveSpeed;
	float mRawPickupRange;
};