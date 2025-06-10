#pragma once

#include "UserWidget.h"

class CButton;
class COptionPanelWidget;
class CCharSelectPanelWidget;
class CCreditsPanelWidget;

class CMainMenuWidget : public CUserWidget
{
public:
	CMainMenuWidget();
	virtual ~CMainMenuWidget();

private:
	CButton* mBtnQuit   = nullptr;
	CButton* mBtnOption = nullptr;
	CButton* mBtnBack   = nullptr;

	COptionPanelWidget* mOptionPanel = nullptr;
	CCharSelectPanelWidget* mCharSelectPanel = nullptr;
	CCreditsPanelWidget* mCreditsPanel = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};