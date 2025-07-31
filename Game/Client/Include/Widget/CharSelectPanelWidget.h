#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataTypeUtils.h"

class CButton;
class CCharacterSlot;
class CHighlightSelectedSlotWidget;
class CCharInfoWidget;

// CharacterSelectionPanelWidget
class CCharSelectPanelWidget : public CUserWidget
{
public:
	CCharSelectPanelWidget();
	virtual ~CCharSelectPanelWidget();

private:
	CCharacterSlot* mPrevSlot = nullptr;
	CHighlightSelectedSlotWidget* mHighlight = nullptr;
	CCharInfoWidget* mInfo = nullptr;
	CButton* mBtnConfirm = nullptr;
	CButton* mBtnStart = nullptr;

protected:
	virtual void Construct() override;
	virtual void Release() override;

public:
	void OnBackButton();
	void OnSlotClicked(CCharacterSlot* slot);

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CCharacterSlot* CreateCharacterSlot(ECharacterType type, const FVector2D& scale, const FVector2D& pos);
};