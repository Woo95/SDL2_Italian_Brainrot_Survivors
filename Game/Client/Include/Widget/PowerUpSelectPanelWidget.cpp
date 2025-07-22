#include "PowerUpSelectPanelWidget.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CPowerUpSelectPanelWidget::CPowerUpSelectPanelWidget()
{
	Construct();
}

CPowerUpSelectPanelWidget::~CPowerUpSelectPanelWidget()
{
}

void CPowerUpSelectPanelWidget::Construct()
{
	SetInteractable(true);

    CImage* outerPanel = CWidgetUtils::AllocateWidget<CImage>("Image_PowerUpSelectPanelBox");
    outerPanel->GetTransform()->SetRelativeScale(1.0f, 1.0f);
    outerPanel->SetTexture("Texture_UIAtlas");
    outerPanel->SetFrame("PanelBox");
    outerPanel->Set9SlicingCorner(FVector2D(15.f, 15.f));
    outerPanel->SetCornerRatio(1.25f);
    AddChild(outerPanel);

    CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("Text_PowerUpSelectCategory");
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
    btnRefundPowerUps->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnRefundPowerUps->SetCornerRatio(1.7f);
    btnRefundPowerUps->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});

    ///// Slot-Related Code - BEGIN /////
    const FVector2D slotScale = FVector2D(0.217f, 0.188f);
    const FVector2D slotStartPos = outerPanel->GetTransform()->GetRelativeScale() * FVector2D(0.032f, 0.23f);
    float offsetX = slotScale.x * 1.1f;
    float offsetY = slotScale.y * 1.1f;

    CPowerUpSlotWidget* mightSlot = CreatePowerUpSlotWidget("Might", slotScale, slotStartPos);
    CPowerUpSlotWidget* armorSlot = CreatePowerUpSlotWidget("Armor", slotScale, mightSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    CPowerUpSlotWidget* maxHpSlot = CreatePowerUpSlotWidget("Max Health", slotScale, armorSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    CPowerUpSlotWidget* recoverySlot = CreatePowerUpSlotWidget("Recovery", slotScale, maxHpSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));

    CPowerUpSlotWidget* speedSlot = CreatePowerUpSlotWidget("Speed", slotScale, mightSlot->GetTransform()->GetRelativePos() + FVector2D(0.0f, offsetY));
    CPowerUpSlotWidget* moveSpeedSlot = CreatePowerUpSlotWidget("Move Speed", slotScale, speedSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    CPowerUpSlotWidget* magnetSlot = CreatePowerUpSlotWidget("Magnet", slotScale, moveSpeedSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));
    CPowerUpSlotWidget* growthSlot = CreatePowerUpSlotWidget("Growth", slotScale, magnetSlot->GetTransform()->GetRelativePos() + FVector2D(offsetX, 0.0f));

    mHighlight = CWidgetUtils::AllocateWidget<CHighlightSelectedSlotWidget, 2>("HighlighSelectedSlot_PowerUp");
    mHighlight->GetTransform()->SetRelativeScale(slotScale * 1.1f);
    mHighlight->Disable();
    AddChild(mHighlight);
    ///// Slot-Related Code - END /////
}

void CPowerUpSelectPanelWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPowerUpSelectPanelWidget>(this);
}

void CPowerUpSelectPanelWidget::OnBackButton()
{
    mHighlight->Disable();
}

void CPowerUpSelectPanelWidget::OnSlotClicked(CPowerUpSlotWidget* slot)
{
    // UI 
    mHighlight->Enable();
    mHighlight->SetSlot(slot);
}

CButton* CPowerUpSelectPanelWidget::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button_" + widgetName);
    button->GetTransform()->SetRelativeScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("Text_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}

CPowerUpSlotWidget* CPowerUpSelectPanelWidget::CreatePowerUpSlotWidget(const std::string& widgetName, const FVector2D& scale, const FVector2D& pos)
{
    CPowerUpSlotWidget* slot = CWidgetUtils::AllocateWidget<CPowerUpSlotWidget, 12>("PowerUpSlot_" + widgetName);
    slot->GetTransform()->SetRelativeScale(scale);
    slot->GetTransform()->SetRelativePos(pos);
    slot->GetTextBlock()->SetText(widgetName);
    slot->SetOnClick([this](CPowerUpSlotWidget* slot) {this->OnSlotClicked(slot);});
    AddChild(slot);

    return slot;
}