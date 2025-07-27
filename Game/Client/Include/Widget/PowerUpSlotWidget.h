#pragma once

#include "SlotWidget.h"
#include "../Core/Utils/GameDataUtils.h"

class CTextBlock;
class CImage;

class CPowerUpSlotWidget : public CSlotWidget
{
public:
	CPowerUpSlotWidget();
	virtual ~CPowerUpSlotWidget();

private:
	EPowerUpType mType = EPowerUpType::NONE;
	bool mIsPurchased = false;

	CImage* mPanel = nullptr;
	CTextBlock* mNameText = nullptr;
	CImage* mIconImage = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	void OnPurchase(bool purchased);

	const EPowerUpType& GetType() const { return mType; }
	bool IsPurchased() const { return mIsPurchased; }
	CTextBlock* GetNameTextBlock() const { return mNameText; }
	CImage* GetIconImage() const { return mIconImage; }

	void SetType(EPowerUpType type)
	{
		mType = type;
	}
};