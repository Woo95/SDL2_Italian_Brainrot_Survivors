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

	// 기본 스탯 (파워업 적용 전)
	float mBaseAttack      = 0.0f;
	float mBaseDefense     = 0.0f;
	float mBaseMaxHP       = 0.0f;
	float mBaseAttackSpeed = 0.0f;
	float mBaseMoveSpeed   = 0.0f;
	float mBasePickupRange = 0.0f;
	float mBaseGrowthExp   = 0.0f;
};