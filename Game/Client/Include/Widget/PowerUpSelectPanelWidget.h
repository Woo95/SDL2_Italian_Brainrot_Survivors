#pragma once

#include "UserWidget.h"

class CButton;
// class CPowerUpSlotWidget; // Need to Implement
class CSelectHighlightWidget;
// class CPowerUpInfoWidget; // Need to Implement

class CPowerUpSelectPanelWidget : public CUserWidget
{
public:
	CPowerUpSelectPanelWidget();
	virtual ~CPowerUpSelectPanelWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
};