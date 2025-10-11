#pragma once

#include "WeaponComponent.h"

class CBubbleWeaponComponent : public CWeaponComponent
{
public:
	CBubbleWeaponComponent();
	virtual ~CBubbleWeaponComponent();

private:
	FVector2D mShootDirs[5] = {};

	float mCooldownTimer = 0.0f;
	const float CONST_COOLDOWN_TIMER = 0.75f;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	virtual void Upgrade() final;

private:
	void Attack();
};