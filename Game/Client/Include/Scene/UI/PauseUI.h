#pragma once

#include "SceneUI.h"

class CButton;
class COptionPanelWidget;

class CPauseUI : public CSceneUI
{
public:
	CPauseUI();
	virtual ~CPauseUI();

private:
	CButton* mBtnQuit   = nullptr;
	CButton* mBtnOption = nullptr;
	CButton* mBtnResume = nullptr;

	COptionPanelWidget* mOptionPanel = nullptr;

public:
	virtual bool Init() final;

private:
	void ShowPanel(CWidget* panel);
	void HidePanel();

	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};