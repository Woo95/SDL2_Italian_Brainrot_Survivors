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
	std::string mKey;

	CTextBlock* mPowerUpName = nullptr;
	CImage* mPowerUpIcon = nullptr;

	std::function<void(CPowerUpSlotWidget*)> mOnClickCallback = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	const std::string& GetKey() const { return mKey; }
	CTextBlock* GetTextBlock() const { return mPowerUpName; }
	CImage* GetImagePowerUpIcon() const { return mPowerUpIcon; }

	void SetKey(const std::string& key)
	{
		mKey = key;
	}
	void SetOnClick(std::function<void(CPowerUpSlotWidget*)> callback)
	{
		mOnClickCallback = callback;
	}
};