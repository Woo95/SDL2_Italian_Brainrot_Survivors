#pragma once

#include "UserWidget.h"

class CTextBlock;
class CImage;
class CButton;
class CPowerUpSlot;

class CPowerUpInfoPanel : public CUserWidget
{
public:
    CPowerUpInfoPanel();
    virtual ~CPowerUpInfoPanel();

protected:
    virtual void Construct() final;
    virtual void Release() final;

private:
    CTextBlock* mName = nullptr;
    CTextBlock* mDescription = nullptr;
    CImage* mMoneyIcon = nullptr;
    CTextBlock* mPrice = nullptr;
    CImage* mPowerUpIcon = nullptr;
    CButton* mBtnBuy = nullptr;

public:
    void ShowInfo(CPowerUpSlot* slot);
    void OnPurchase(bool purchased);

private:
    CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};