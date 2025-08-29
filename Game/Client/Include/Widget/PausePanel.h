#pragma once

#include "UserWidget.h"

class CButton;
class COptionPanel;

class CPausePanel : public CUserWidget
{
public:
	CPausePanel();
	virtual ~CPausePanel();

private:
	CButton* mBtnQuit   = nullptr;
	CButton* mBtnOption = nullptr;
	CButton* mBtnResume = nullptr;

	COptionPanel* mOptionPanel = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};