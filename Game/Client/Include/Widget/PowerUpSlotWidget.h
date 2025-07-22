#pragma once

#include "SlotWidget.h"

class CTextBlock;

class CPowerUpSlotWidget : public CSlotWidget
{
public:
	CPowerUpSlotWidget();
	virtual ~CPowerUpSlotWidget();

private:
	CTextBlock* mPowerUpName = nullptr;

	std::function<void(CPowerUpSlotWidget*)> mOnClickCallback = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	CTextBlock* GetTextBlock() const { return mPowerUpName; }

	void SetOnClick(std::function<void(CPowerUpSlotWidget*)> callback)
	{
		mOnClickCallback = callback;
	}
};