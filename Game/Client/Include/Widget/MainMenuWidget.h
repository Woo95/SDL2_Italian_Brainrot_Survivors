#pragma once

#include "UserWidget.h"

class CButton;
class CMoneyHUDWidget;
class COptionPanel;
class CCharacterSelectPanel;
class CPowerUpSelectPanelWidget;
class CCreditsPanelWidget;

class CMainMenuWidget : public CUserWidget
{
public:
	CMainMenuWidget();
	virtual ~CMainMenuWidget();

private:
	CButton* mBtnQuit    = nullptr;
	CButton* mBtnOption  = nullptr;
	CButton* mBtnBack    = nullptr;
	CButton* mBtnStart   = nullptr;
	CButton* mBtnPowerUp = nullptr;
	CButton* mBtnCredits = nullptr;

	CMoneyHUDWidget* mMoneyHUD;
	COptionPanel* mOptionPanel = nullptr;
	CCharacterSelectPanel* mCharSelectPanel = nullptr;
	CPowerUpSelectPanelWidget* mPowerUpSelectPanel = nullptr;
	CCreditsPanelWidget* mCreditsPanel = nullptr;

protected:
	virtual void Construct() override;
	virtual void Update(float deltaTime) override;
	virtual void Release() override;

public:
	CMoneyHUDWidget* GetMoneyHUD() const { return mMoneyHUD; }

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();
	void OnBackButton();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};