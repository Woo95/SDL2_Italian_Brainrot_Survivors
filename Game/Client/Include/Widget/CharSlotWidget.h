#pragma once

#include "UserWidget.h"

class CTextBlock;

class CCharSlotWidget : public CUserWidget
{
public:
	CCharSlotWidget();
	virtual ~CCharSlotWidget();

private:
	CTextBlock* mName;
	std::string mSFX;

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	void SetName(const std::string& name);
	void SetSFX(const std::string& sfx);
};