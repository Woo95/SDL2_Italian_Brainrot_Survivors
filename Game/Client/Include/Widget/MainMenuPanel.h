#pragma once

#include "UserWidget.h"

class CButton;
class CMoneyHUD;
class COptionPanel;
class CCharacterSelectPanel;
class CPowerUpSelectPanel;
class CCreditsPanel;

class CMainMenuPanel : public CUserWidget
{
public:
	CMainMenuPanel();
	virtual ~CMainMenuPanel();

private:
	CButton* mBtnQuit    = nullptr;
	CButton* mBtnOption  = nullptr;
	CButton* mBtnBack    = nullptr;
	CButton* mBtnStart   = nullptr;
	CButton* mBtnPowerUp = nullptr;
	CButton* mBtnCredits = nullptr;

	CMoneyHUD* mMoneyHUD;
	COptionPanel* mOptionPanel = nullptr;
	CCharacterSelectPanel* mCharSelectPanel = nullptr;
	CPowerUpSelectPanel* mPowerUpSelectPanel = nullptr;
	CCreditsPanel* mCreditsPanel = nullptr;

protected:
	virtual void Construct() final;
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	CMoneyHUD* GetMoneyHUD() const { return mMoneyHUD; }

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();
	void OnBackButton();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};