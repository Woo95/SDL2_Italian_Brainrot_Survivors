#pragma once

#include "UserWidget.h"

class CButton;
class CCharSlotWidget;
class CHighlightSelectedSlotWidget;
class CCharInfoWidget;

// CharacterSelectionPanelWidget
class CCharSelectPanelWidget : public CUserWidget
{
public:
	CCharSelectPanelWidget();
	virtual ~CCharSelectPanelWidget();

private:
	CCharSlotWidget* mPrevSlot = nullptr;
	CHighlightSelectedSlotWidget* mHighlight = nullptr;
	CCharInfoWidget* mInfo = nullptr;
	CButton* mBtnConfirm = nullptr;
	CButton* mBtnStart = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void OnBackButton();

private:
	void OnSlotClicked(CCharSlotWidget* slot);
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CCharSlotWidget* CreateCharSlotWidget(const std::string& widgetName, const FVector2D& scale, const FVector2D& pos);
};