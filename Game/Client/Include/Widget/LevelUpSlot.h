#pragma once

#include "Slot.h"
#include "../Core/Utils/GameDataUtils.h"

class CTextBlock;
class CImage;

class CLevelUpSlot : public CSlot
{
public:
	CLevelUpSlot();
	virtual ~CLevelUpSlot();

private:
	FItem mItem;

	CTextBlock* mName = nullptr;
	CTextBlock* mStatus = nullptr;
	CTextBlock* mDescription = nullptr;
	CImage* mWeaponIcon = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	void UpdateSlot(const FItem& item);

private:
	void UpdateSlotData(const std::string& name, const std::string& description, const std::string& iconFrame, int level);
};