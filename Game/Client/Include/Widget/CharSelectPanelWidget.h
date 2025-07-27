#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataTypeUtils.h"

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
	void OnSlotClicked(CCharSlotWidget* slot);

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CCharSlotWidget* CreateCharSlotWidget(ECharacterType type, const FVector2D& scale, const FVector2D& pos);
};