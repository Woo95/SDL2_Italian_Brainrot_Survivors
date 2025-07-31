#include "PowerUpSlot.h"
#include "AllWidgets.h"

CPowerUpSlot::CPowerUpSlot()
{
    Construct();
}

CPowerUpSlot::~CPowerUpSlot()
{
}

void CPowerUpSlot::Construct()
{
    SetInteractable(true);

    mPanel = CWidgetUtils::AllocateWidget<CImage>("PowerUpSlot_Image_Panel");
    mPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    mPanel->GetTransform()->SetPivot(0.5f, 0.5f);
    mPanel->SetTexture("Texture_UIAtlas");
    mPanel->SetFrame("SelectSlot");
    mPanel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    mPanel->SetCornerRatio(1.25f);
    AddChild(mPanel);

    mNameText = CWidgetUtils::AllocateWidget<CTextBlock>("PowerUpSlot_Text_Name");
    mNameText->GetTransform()->SetRelativeScale(0.9f, 0.2f);
    mNameText->GetTransform()->SetPivot(0.5f, 2.2f);
    mNameText->SetAlignment(ETextBlock::Alignment::CENTER);
    mNameText->SetCharWidth(14.0f);
    mNameText->SetFont("Font64_CourierPrime_Regular");
    mNameText->SetColor(59, 59, 59);
    mPanel->AddChild(mNameText);

    CImage* powerUpBox = CWidgetUtils::AllocateWidget<CImage>("PowerUpSlot_Image_PowerUpBox");
    powerUpBox->GetTransform()->SetRelativeScale(FVector2D(0.4f, 0.4f));
    powerUpBox->GetTransform()->SetPivot(0.5f, 0.5f);
    powerUpBox->SetTexture("Texture_UIAtlas");
    powerUpBox->SetFrame("PowerUpBox");
    mPanel->AddChild(powerUpBox);

    mIconImage = CWidgetUtils::AllocateWidget<CImage>("PowerUpSlot_Image_PowerUpIcon");
    mIconImage->GetTransform()->SetRelativeScale(FVector2D(0.7f, 0.7f));
    mIconImage->GetTransform()->SetPivot(0.5f, 0.5f);
    mIconImage->SetTexture("Texture_ItemAtlas");
    mIconImage->SetFrame("Empty");
    powerUpBox->AddChild(mIconImage);
}

void CPowerUpSlot::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPowerUpSlot>(this);
}

void CPowerUpSlot::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        CPowerUpSelectPanel* panel = dynamic_cast<CPowerUpSelectPanel*>(mParent);
        panel->SetSelectedSlot(this);
        panel->OnSlotClicked(this);
    }
}

void CPowerUpSlot::OnPurchase(bool purchased)
{
    if (purchased)
    {
        mIsPurchased = true;
        mPanel->SetColor(200, 200, 0);
        mNameText->SetColor(255, 255, 255);
    }
    else
    {
        mIsPurchased = false;
        mPanel->SetColor(255, 255, 255);
        mNameText->SetColor(59, 59, 59);
    }
}