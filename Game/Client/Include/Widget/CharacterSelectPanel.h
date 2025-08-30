#pragma once

#include "UserWidget.h"
#include "../Core/Utils/GameDataUtils.h"

class CButton;
class CCharacterSlot;
class CHighlightSelectedSlot;
class CCharacterInfoPanel;

class CCharacterSelectPanel : public CUserWidget
{
public:
	CCharacterSelectPanel();
	virtual ~CCharacterSelectPanel();

private:
	CCharacterSlot* mPrevSlot = nullptr;
	CHighlightSelectedSlot* mHighlight = nullptr;
	CCharacterInfoPanel* mInfoPanel = nullptr;
	CButton* mBtnConfirm = nullptr;
	CButton* mBtnStart = nullptr;

protected:
	virtual void Construct() final;
	virtual void Release() final;

public:
	void OnBackButton();
	void OnSlotClicked(CCharacterSlot* slot);

private:
	CButton* CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize);
	CCharacterSlot* CreateCharacterSlot(ECharacterType type, const FVector2D& scale, const FVector2D& pos);
};