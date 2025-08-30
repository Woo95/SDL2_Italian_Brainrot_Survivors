#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataUtils.h"

class CButton;
class CPowerUpSlot;
class CHighlightSelectedSlot;
class CPowerUpInfoPanel;

class CPowerUpSelectPanel : public CUserWidget
{
public:
	CPowerUpSelectPanel();
	virtual ~CPowerUpSelectPanel();

private:
	CPowerUpSlot* mSelectedSlot = nullptr;
	CPowerUpSlot* mSlots[(int)EPowerUpType::MAX] = {};
	CHighlightSelectedSlot* mHighlight = nullptr;
	CPowerUpInfoPanel* mInfo = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void OnRefundButton();
	void OnBuyButton();
	void OnBackButton();
	void OnSlotClicked(CPowerUpSlot* slot);

	void SetSelectedSlot(CPowerUpSlot* slot) { mSelectedSlot = slot; }

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CPowerUpSlot* CreatePowerUpSlot(EPowerUpType type, const FVector2D& scale, const FVector2D& pos, const std::string& textLabel);
	const FVector2D CalcSlotPos(int col, int row) const;
};