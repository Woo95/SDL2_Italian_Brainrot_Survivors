#pragma once

#include "WeaponComponent.h"

class CBanana;

class CBananaWeaponComponent : public CWeaponComponent
{
public:
	CBananaWeaponComponent();
	virtual ~CBananaWeaponComponent();

private:
	CBanana* mBanana = nullptr;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	virtual void Upgrade() final;
};