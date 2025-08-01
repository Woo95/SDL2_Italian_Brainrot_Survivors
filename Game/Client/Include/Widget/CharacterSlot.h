#pragma once

#include "Slot.h"
#include "../Core/Utils/GameDataTypeUtils.h"

class CTextBlock;
class CAnimatedImage;
class CImage;

class CCharacterSlot : public CSlot
{
public:
	CCharacterSlot();
	virtual ~CCharacterSlot();

private:
	ECharacterType mType = ECharacterType::NONE;

	CTextBlock* mNameText = nullptr;
	CAnimatedImage* mCharacter = nullptr;
	CImage* mWeaponIcon = nullptr;
	std::string mSFX;

protected:
	virtual void Construct() final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;

public:
	const ECharacterType& GetType() const { return mType; }
	CTextBlock* GetNameTextBlock() const { return mNameText; }
	CAnimatedImage* GetAnimatedImage() const { return mCharacter; }
	CImage* GetWeaponIconImage() const { return mWeaponIcon; }

	void SetType(ECharacterType type)
	{
		mType = type;
	}
	void SetSFX(const std::string& sfx)
	{
		mSFX = sfx;
	}

	void PlaySFX();
	void StopSFX();
};