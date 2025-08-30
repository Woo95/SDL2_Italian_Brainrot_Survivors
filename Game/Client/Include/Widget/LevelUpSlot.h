#pragma once

#include "Slot.h"

class CTextBlock;
class CImage;

class CLevelUpSlot : public CSlot
{
public:
	CLevelUpSlot();
	virtual ~CLevelUpSlot();

private:
	CTextBlock* mName = nullptr;
	CTextBlock* mNew  = nullptr;
	CTextBlock* mDescription = nullptr;
	CImage* mWeaponIcon = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;
};