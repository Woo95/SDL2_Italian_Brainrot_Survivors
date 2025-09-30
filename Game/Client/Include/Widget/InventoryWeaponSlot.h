#pragma once

#include "Slot.h"
#include "../Core/Utils/GameDataUtils.h"

class CImage;

class CInventoryWeaponSlot : public CSlot
{
public:
	CInventoryWeaponSlot();
	virtual ~CInventoryWeaponSlot();

private:
	CImage* mItemIcon = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void UpdateSlot(EWeaponType type);
};