#pragma once

#include "SlotWidget.h"
#include "../Core/Utils/CharacterUtils.h"

class CTextBlock;

class CCharSlotWidget : public CSlotWidget
{
public:
	CCharSlotWidget();
	virtual ~CCharSlotWidget();

private:
	ECharacterType mCharType = ECharacterType::NONE;
	CTextBlock* mCharName = nullptr;
	std::string mSFX;

	std::function<void(CCharSlotWidget*)> mOnClickCallback = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	ECharacterType GetCharType() const { return mCharType; }

	void SetCharType(ECharacterType type);
	void SetText(const std::string& name);
	void SetSFX(const std::string& sfx);
	void SetOnClick(std::function<void(CCharSlotWidget*)> callback);

	void StopSFX();
};