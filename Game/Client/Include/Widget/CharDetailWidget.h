#pragma once

#include "UserWidget.h"

class CTextBlock;
class CImage;
class CSlotWidget;

class CCharDetailWidget : public CUserWidget
{
public:
    CCharDetailWidget();
    virtual ~CCharDetailWidget();

protected:
    virtual void Construct() override;
    virtual void Release() override;

private:
    CTextBlock* mName;
    CTextBlock* mDescription;
    CImage* mCharacter;
    CImage* mWeaponBox;
    CImage* mWeapon;

public:
    void ShowDetail(CSlotWidget* slot);
};