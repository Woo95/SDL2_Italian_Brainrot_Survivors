#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataTypeUtils.h"

class CButton;
class CPowerUpSlotWidget;
class CHighlightSelectedSlot;
class CPowerUpInfoWidget;

class CPowerUpSelectPanelWidget : public CUserWidget
{
public:
	CPowerUpSelectPanelWidget();
	virtual ~CPowerUpSelectPanelWidget();

private:
	CPowerUpSlotWidget* mSelectedSlot = nullptr;
	CPowerUpSlotWidget* mSlots[(int)EPowerUpType::MAX] = {};
	CHighlightSelectedSlot* mHighlight = nullptr;
	CPowerUpInfoWidget* mInfo = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void OnRefundButton();
	void OnBuyButton();
	void OnBackButton();
	void OnSlotClicked(CPowerUpSlotWidget* slot);

	void SetSelectedSlot(CPowerUpSlotWidget* slot) { mSelectedSlot = slot; }

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CPowerUpSlotWidget* CreatePowerUpSlotWidget(EPowerUpType type, const FVector2D& scale, const FVector2D& pos, const std::string& textLabel);
	const FVector2D CalcSlotPos(int col, int row) const;
};