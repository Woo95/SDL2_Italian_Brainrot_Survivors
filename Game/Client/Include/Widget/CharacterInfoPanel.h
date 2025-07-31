#pragma once

#include "UserWidget.h"

class CTextBlock;
class CImage;
class CCharacterSlot;

class CCharacterInfoPanel : public CUserWidget
{
public:
    CCharacterInfoPanel();
    virtual ~CCharacterInfoPanel();

protected:
    virtual void Construct() override;
    virtual void Release() override;

private:
    CTextBlock* mName = nullptr;
    CTextBlock* mDescription1 = nullptr;
    CTextBlock* mDescription2 = nullptr;
    CImage* mCharacter = nullptr;
    CImage* mWeaponIcon = nullptr;

public:
    void ShowInfo(CCharacterSlot* slot);
};