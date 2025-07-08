#pragma once

#include "UserWidget.h"

class CButton;
class COptionPanelWidget;

class CPauseWidget : public CUserWidget
{
public:
	CPauseWidget();
	virtual ~CPauseWidget();

private:
	CButton* mBtnQuit   = nullptr;
	CButton* mBtnOption = nullptr;
	CButton* mBtnResume = nullptr;

	COptionPanelWidget* mOptionPanel = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};