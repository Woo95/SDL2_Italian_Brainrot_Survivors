#pragma once

#include "UserWidget.h"

class CButton;
class CPowerUpSlotWidget;
class CHighlightSelectedSlotWidget;
class CPowerUpInfoWidget;

class CPowerUpSelectPanelWidget : public CUserWidget
{
public:
	CPowerUpSelectPanelWidget();
	virtual ~CPowerUpSelectPanelWidget();

private:
	CHighlightSelectedSlotWidget* mHighlight = nullptr;
	CPowerUpInfoWidget* mInfo = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void OnBackButton();

private:
	void OnSlotClicked(CPowerUpSlotWidget* slot);
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CPowerUpSlotWidget* CreatePowerUpSlotWidget(const std::string& widgetName, const FVector2D& scale, const FVector2D& pos, const std::string& textLabel);
};