#pragma once

#include "Component.h"

class CStatusComponent : public CComponent
{
public:
	CStatusComponent();
	virtual ~CStatusComponent();

private:
	// 체력
	float mMaxHP;
	float mCurrentHP;

	// 기본 스탯
	float mAttack;
	float mDefense;
	float mMoveSpeed;
	float mAttackSpeed;

	// 레벨
	int mLevel;
	float mExpToLevelUp;
	float mCurrentExp;

private:
	virtual bool Init() final;
	virtual void Release() final;
};