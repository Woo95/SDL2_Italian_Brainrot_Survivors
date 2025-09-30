#pragma once

#include "Slot.h"
#include "../Core/Utils/GameDataUtils.h"

class CImage;

class CInventoryPowerUpSlot : public CSlot
{
public:
	CInventoryPowerUpSlot();
	virtual ~CInventoryPowerUpSlot();

private:
	CImage* mItemIcon = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void UpdateSlot(EPowerUpType type);
};