#pragma once

#include "UserWidget.h"

class CImage;
class CButton;
class CTextBlock;
class CMoneyHUDWidget;

class CMainMenuWidget : public CUserWidget
{
public:
	CMainMenuWidget();
	virtual ~CMainMenuWidget();

private:
	CImage* mMenuTopBar;
	CTextBlock* mName;
	CMoneyHUDWidget* mMoneyHUD;

	CButton* mBtnQuit;
	CButton* mBtnOption;
	CButton* mStart;
	CButton* mPowerUp;

protected:
	virtual void Construct() override;
	virtual void Release() override;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};