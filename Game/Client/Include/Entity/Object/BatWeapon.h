#pragma once

#include "Weapon.h"

class CBatWeapon : public CWeapon
{
public:
	CBatWeapon();
	virtual ~CBatWeapon();

private:
	int mProjectile;
	float mCooldown;
	float mWeaponAttack;
	float mWeaponRange;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	virtual void AddWeaponLevel() final;
};