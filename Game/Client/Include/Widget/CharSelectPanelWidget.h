#pragma once

#include "UserWidget.h"

class CButton;
class CCharSlotWidget;
class CSelectHighlightWidget;
class CCharDetailWidget;

// CharacterSelectionPanelWidget
class CCharSelectPanelWidget : public CUserWidget
{
public:
	CCharSelectPanelWidget();
	virtual ~CCharSelectPanelWidget();

private:
	CCharSlotWidget* mSelectedSlot;
	CSelectHighlightWidget* mHighlight;
	CCharDetailWidget* mDetail;

protected:
	virtual void Construct() override;
	virtual void Release() override;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	void OnSlotClicked(CCharSlotWidget* slot);
};