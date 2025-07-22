#pragma once

#include "SlotWidget.h"
#include "../Core/Utils/CharacterUtils.h"

class CTextBlock;
class CAnimatedImage;

class CCharSlotWidget : public CSlotWidget
{
public:
	CCharSlotWidget();
	virtual ~CCharSlotWidget();

private:
	ECharacterType mCharType = ECharacterType::NONE;
	CAnimatedImage* mCharacter = nullptr;
	CTextBlock* mCharName = nullptr;
	std::string mSFX;

	std::function<void(CCharSlotWidget*)> mOnClickCallback = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	ECharacterType GetCharType() const { return mCharType; }
	CAnimatedImage* GetAnimatedImage() const { return mCharacter; }
	CTextBlock* GetTextBlock() const { return mCharName; }

	void SetCharacterType(ECharacterType type)
	{
		mCharType = type;
	}
	void SetSFX(const std::string& sfx)
	{
		mSFX = sfx;
	}
	void SetOnClick(std::function<void(CCharSlotWidget*)> callback)
	{
		mOnClickCallback = callback;
	}

	void PlaySFX();
	void StopSFX();
};