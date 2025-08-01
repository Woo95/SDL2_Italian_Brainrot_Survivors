#include "PowerUpSelectPanel.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerState.h"
#include "../Manager/Data/GameData/PowerUpDataManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CPowerUpSelectPanel::CPowerUpSelectPanel()
{
	Construct();
}

CPowerUpSelectPanel::~CPowerUpSelectPanel()
{
}

void CPowerUpSelectPanel::Construct()
{
	SetInteractable(true);

    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("PowerUpSelectPanel_Image_OuterPanel");
    outerPanel->GetTransform()->SetRelativeScale(1.0f, 1.0f);
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpSelectPanel_TextBlock_Category");
    category->GetTransform()->SetRelativeScale(outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.7f, 0.065f));
    category->GetTransform()->SetRelativePos(outerPanel->GetTransform()->GetRelativePos() +
        FVector2D(outerPanel->GetTransform()->GetRelativeScale().x * 0.5f - category->GetTransform()->GetRelativeScale().x * 0.5f, outerPanel->GetTransform()->GetRelativeScale().y * 0.0325f));
    category->SetAlignment(ETextBlock::Alignment::CENTER);
    category->SetCharWidth(50.f);
    category->SetFont("Font64_CourierPrime_Regular");
    category->SetText("PowerUp Selection");
    AddChild(category);

    CButton* btnRefundPowerUps = CreateButton("RefundPowerUps", "BlueButton", FVector2D(0.8f, 0.095f), "Refund PowerUps", FVector2D(0.5f, 0.5f));
    btnRefundPowerUps->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.15f));
    btnRefundPowerUps->Set9SlicingCorner(FVector2D(10.0f, 7.0f));
    btnRefundPowerUps->SetCornerRatio(1.7f);
    btnRefundPowerUps->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    btnRefundPowerUps->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->OnRefundButton();});

    ///// Slot-Related Code - BEGIN /////
    const FVector2D slotScale = FVector2D(0.217f, 0.188f);
    const FVector2D slotStartPos = outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.14f, 0.32f);

    mSlots[(int)EPowerUpType::MIGHT]      = CreatePowerUpSlot(EPowerUpType::MIGHT,      slotScale, slotStartPos + CalcSlotPos(0 ,0), "Might");
    mSlots[(int)EPowerUpType::ARMOR]      = CreatePowerUpSlot(EPowerUpType::ARMOR,      slotScale, slotStartPos + CalcSlotPos(1, 0), "Armor");
    mSlots[(int)EPowerUpType::MAX_HEALTH] = CreatePowerUpSlot(EPowerUpType::MAX_HEALTH, slotScale, slotStartPos + CalcSlotPos(2, 0), "Max Health");
    mSlots[(int)EPowerUpType::RECOVERY]   = CreatePowerUpSlot(EPowerUpType::RECOVERY,   slotScale, slotStartPos + CalcSlotPos(3, 0), "Recovery");

    mSlots[(int)EPowerUpType::SPEED]      = CreatePowerUpSlot(EPowerUpType::SPEED,      slotScale, slotStartPos + CalcSlotPos(0, 1), "Speed");
    mSlots[(int)EPowerUpType::MOVE_SPEED] = CreatePowerUpSlot(EPowerUpType::MOVE_SPEED, slotScale, slotStartPos + CalcSlotPos(1, 1), "Move Speed");
    mSlots[(int)EPowerUpType::MAGNET]     = CreatePowerUpSlot(EPowerUpType::MAGNET,     slotScale, slotStartPos + CalcSlotPos(2, 1), "Magnet");
    mSlots[(int)EPowerUpType::GROWTH]     = CreatePowerUpSlot(EPowerUpType::GROWTH,     slotScale, slotStartPos + CalcSlotPos(3, 1), "Growth");

    mHighlight = CWidgetUtils::AllocateWidget<CHighlightSelectedSlot, 2>("PowerUpSelectPanel_HighlightSelectedSlot");
    mHighlight->Disable();
    AddChild(mHighlight);

    mInfo = CWidgetUtils::AllocateWidget<CPowerUpInfoPanel, 1>("PowerUpSelectPanel_PowerUpInfoPanel");
    mInfo->GetTransform()->SetRelativeScale(FVector2D(0.957f, 0.177f));
    mInfo->GetTransform()->SetRelativePos(FVector2D(0.02f, 0.805f));
    mInfo->Disable();
    AddChild(mInfo);
    ///// Slot-Related Code - END /////
}

void CPowerUpSelectPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPowerUpSelectPanel>(this);
}

void CPowerUpSelectPanel::OnRefundButton()
{
    CPlayerState* playerState = CGameDataManager::GetInst()->GetPlayerState();
    if (!playerState->RefundAllPowerUp())
        return;

    mInfo->OnPurchase(false);
    for (CPowerUpSlot* slot : mSlots)
        slot->OnPurchase(false);

    if (CMainMenuPanel* menu = dynamic_cast<CMainMenuPanel*>(mParent))
        menu->GetMoneyHUD()->SetBalance(playerState->GetBalance());
}

void CPowerUpSelectPanel::OnBuyButton()
{
    CPlayerState* playerState = CGameDataManager::GetInst()->GetPlayerState();
    if (!playerState->PurchasePowerUp(mSelectedSlot->GetType()))
        return;

    mInfo->OnPurchase(true);
    mSelectedSlot->OnPurchase(true);

    if (CMainMenuPanel* menu = dynamic_cast<CMainMenuPanel*>(mParent))
        menu->GetMoneyHUD()->SetBalance(playerState->GetBalance());
}

void CPowerUpSelectPanel::OnBackButton()
{
    mHighlight->Disable();
    mInfo->Disable();
}

void CPowerUpSelectPanel::OnSlotClicked(CPowerUpSlot* slot)
{
    // UI 
    mHighlight->Enable();
    mHighlight->SetSlot(mSelectedSlot);
    mInfo->Enable();
    mInfo->ShowInfo(mSelectedSlot);
}

CButton* CPowerUpSelectPanel::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("PowerUpSelectPanel_Button_" + widgetName);
    button->GetTransform()->SetRelativeScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpSelectPanel_TextBlock_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}

CPowerUpSlot* CPowerUpSelectPanel::CreatePowerUpSlot(EPowerUpType type, const FVector2D& scale, const FVector2D& pos, const std::string& textLabel)
{
    const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetPowerUpDataManager()->GetPowerUpData(type);

    CPowerUpSlot* slot = CWidgetUtils::AllocateWidget<CPowerUpSlot, 12>("PowerUpSelectPanel_PowerUpSlot_" + powerUpData.name);
    slot->SetType(type);

    slot->GetTransform()->SetRelativeScale(scale);
    slot->GetTransform()->SetRelativePos(pos);
    slot->GetTransform()->SetPivot(0.5f, 0.5f);

    slot->GetNameTextBlock()->SetText(textLabel);
    slot->GetIconImage()->SetFrame(powerUpData.name);
    slot->OnPurchase(CGameDataManager::GetInst()->GetPlayerState()->IsPowerUpOwned(slot->GetType()));
    AddChild(slot);

    return slot;
}

const FVector2D CPowerUpSelectPanel::CalcSlotPos(int col, int row) const
{
    const FVector2D slotScale = FVector2D(0.217f, 0.188f);
    const float offsetX = slotScale.x * 1.1f;
    const float offsetY = slotScale.y * 1.1f;

    return FVector2D(offsetX * col, offsetY * row);
}