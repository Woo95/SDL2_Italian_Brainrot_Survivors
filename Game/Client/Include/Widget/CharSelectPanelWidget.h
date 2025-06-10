#pragma once

#include "UserWidget.h"

class CButton;
class CCharSlotWidget;
class CSelectHighlightWidget;
class CCharInfoWidget;

// CharacterSelectionPanelWidget
class CCharSelectPanelWidget : public CUserWidget
{
public:
	CCharSelectPanelWidget();
	virtual ~CCharSelectPanelWidget();

private:
	CCharSlotWidget* mPrevSlot = nullptr;
	CSelectHighlightWidget* mHighlight = nullptr;
	CCharInfoWidget* mDetail = nullptr;
	CButton* mBtnStart = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void OnBackButton();

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	void OnSlotClicked(CCharSlotWidget* slot);
};