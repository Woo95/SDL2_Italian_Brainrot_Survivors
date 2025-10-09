#pragma once

#include "WeaponComponent.h"

class CBatWeaponComponent : public CWeaponComponent
{
public:
	CBatWeaponComponent();
	virtual ~CBatWeaponComponent();

private:
	int mFiredProjectile = 0;
	float mProjectileTimer = 0.0f;
	float mCooldownTimer = 0.0f;

	const float CONST_PROJECTILE_TIMER = 0.1f;
	const float CONST_COOLDOWN_TIMER = 1.2f;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	virtual void Upgrade() final;

private:
	void Attack();
};