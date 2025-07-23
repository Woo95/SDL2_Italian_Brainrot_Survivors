#include "PowerUpSlotWidget.h"
#include "AllWidgets.h"

CPowerUpSlotWidget::CPowerUpSlotWidget()
{
    Construct();
}

CPowerUpSlotWidget::~CPowerUpSlotWidget()
{
}

void CPowerUpSlotWidget::Construct()
{
    SetInteractable(true);

    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("Image_PowerUpSlot");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->GetTransform()->SetPivot(0.5f, 0.5f);
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.25f);
    AddChild(panel);

    mPowerUpName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_PowerUpSlot");
    mPowerUpName->GetTransform()->SetRelativeScale(0.9f, 0.2f);
    mPowerUpName->GetTransform()->SetPivot(0.5f, 2.2f);
    mPowerUpName->SetAlignment(ETextBlock::Alignment::CENTER);
    mPowerUpName->SetCharWidth(14.0f);
    mPowerUpName->SetFont("Font64_CourierPrime_Regular");
    mPowerUpName->SetColor(59, 59, 59);
    panel->AddChild(mPowerUpName);

    CImage* powerUpBox = CWidgetUtils::AllocateWidget<CImage>("Image_PowerUpBox");
    powerUpBox->GetTransform()->SetRelativeScale(FVector2D(0.4f, 0.4f));
    powerUpBox->GetTransform()->SetPivot(0.5f, 0.5f);
    powerUpBox->SetTexture("Texture_UIAtlas");
    powerUpBox->SetFrame("PowerUpBox");
    panel->AddChild(powerUpBox);

    mPowerUpIcon = CWidgetUtils::AllocateWidget<CImage>("Image_PowerUpIcon");
    mPowerUpIcon->GetTransform()->SetRelativeScale(FVector2D(0.7f, 0.7f));
    mPowerUpIcon->GetTransform()->SetPivot(0.5f, 0.5f);
    mPowerUpIcon->SetTexture("Texture_ItemAtlas");
    mPowerUpIcon->SetFrame("Empty");
    powerUpBox->AddChild(mPowerUpIcon);
}

void CPowerUpSlotWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPowerUpSlotWidget>(this);
}

void CPowerUpSlotWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        if (mOnClickCallback)
            mOnClickCallback(this);
    }
}