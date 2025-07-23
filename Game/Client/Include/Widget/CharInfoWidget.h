#pragma once

#include "UserWidget.h"

class CTextBlock;
class CImage;
class CCharSlotWidget;

class CCharInfoWidget : public CUserWidget
{
public:
    CCharInfoWidget();
    virtual ~CCharInfoWidget();

protected:
    virtual void Construct() override;
    virtual void Release() override;

private:
    CTextBlock* mName = nullptr;
    CTextBlock* mDescription1 = nullptr;
    CTextBlock* mDescription2 = nullptr;
    CImage* mCharacter = nullptr;
    CImage* mWeapon    = nullptr;

public:
    void ShowInfo(CCharSlotWidget* slot);
};