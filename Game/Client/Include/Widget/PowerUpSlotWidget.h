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

	CTextBlock* mNameText = nullptr;
	CImage* mIconImage = nullptr;

	std::function<void(CPowerUpSlotWidget*)> mOnClickCallback = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	const EPowerUpType& GetType() const { return mType; }
	CTextBlock* GetNameTextBlock() const { return mNameText; }
	CImage* GetIconImage() const { return mIconImage; }

	void SetType(EPowerUpType type)
	{
		mType = type;
	}
	void SetOnClick(std::function<void(CPowerUpSlotWidget*)> callback)
	{
		mOnClickCallback = callback;
	}
};