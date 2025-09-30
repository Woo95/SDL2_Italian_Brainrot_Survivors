#pragma once

#include "UserWidget.h"
#include "../Core/Utils/InventoryUtils.h"

class CInventoryWeaponSlot;
class CInventoryPowerUpSlot;

class CInventoryPanel : public CUserWidget
{
public:
	CInventoryPanel();
	virtual ~CInventoryPanel();

private:
	CInventoryWeaponSlot* mWeaponSlots[CONST_WIDGET_MAX_WEAPON_SLOT] = {};
	int mWeaponCount = 0;

	CInventoryPowerUpSlot* mPowerUpSlots[CONST_WIDGET_MAX_POWERUP_SLOT] = {};
	int mPowerUpCount = 0;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void AddWeapon(EWeaponType type);
	void AddPowerUp(EPowerUpType type);

private:
	CInventoryWeaponSlot*  CreateWeaponSlot(int idx, const FVector2D& scale, const FVector2D& pos);
	CInventoryPowerUpSlot* CreatePowerUpSlot(int idx, const FVector2D& scale, const FVector2D& pos);
};