#pragma once

#include "Component.h"
#include "../../Core/Utils/GameDataUtils.h"

class CWeaponComponent abstract : public CComponent
{
public:
	CWeaponComponent() = default;
	virtual ~CWeaponComponent() = default;

protected:
	EWeaponType mWeaponType = EWeaponType::NONE;
	int mLevel = 0;
	int mProjectile = 0;
	float mWeaponAttack = 1.0f;

public:
	virtual bool Init() override { return true; };
	virtual void Upgrade() = 0;

public:
	const EWeaponType& GetType() const { return mWeaponType; }
	int GetLevel() const { return mLevel; }
};