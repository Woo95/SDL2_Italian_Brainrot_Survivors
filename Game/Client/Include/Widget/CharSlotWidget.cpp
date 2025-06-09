#include "CharSlotWidget.h"
#include "AllWidgets.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"

CCharSlotWidget::CCharSlotWidget()
{
	Construct();
}

CCharSlotWidget::~CCharSlotWidget()
{
}

void CCharSlotWidget::Construct()
{
    SetInteractable(true);

    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("Image_CharSlot");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.25f);
    AddChild(panel);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CharSlot");
    mName->GetTransform()->SetRelativeScale(0.9f, 0.175f);
    mName->GetTransform()->SetRelativePos(0.05f, 0.1f);
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    AddChild(mName);
}

void CCharSlotWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CCharSlotWidget>(this);
}

void CCharSlotWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);

        if (!sfx->IsPlaying())
            sfx->Play();
    }
}

void CCharSlotWidget::SetName(const std::string& name)
{
    mName->SetText(name);
}

void CCharSlotWidget::SetSFX(const std::string& sfx)
{
    mSFX = sfx;
}