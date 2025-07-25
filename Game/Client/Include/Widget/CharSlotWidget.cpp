#include "CharSlotWidget.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

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
    panel->GetTransform()->SetPivot(0.5f, 0.5f);
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.25f);
    AddChild(panel);

    mNameText = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CharSlot");
    mNameText->GetTransform()->SetRelativeScale(0.9f, 0.175f);
    mNameText->GetTransform()->SetPivot(0.5f, 2.4f);
    mNameText->SetAlignment(ETextBlock::Alignment::LEFT);
    mNameText->SetCharWidth(12.5f);
    mNameText->SetFont("Font64_CourierPrime_Regular");
    panel->AddChild(mNameText);

    mCharacter = CWidgetUtils::AllocateWidget<CAnimatedImage, 3>("AnimatedImage_CharSlot");
    mCharacter->SetAnimating(false);
    panel->AddChild(mCharacter);
}

void CCharSlotWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CCharSlotWidget>(this);
}

void CCharSlotWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        if (mOnClickCallback)
            mOnClickCallback(this);
    }
}

void CCharSlotWidget::PlaySFX()
{
    std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);

    if (!sfx->IsPlaying())
        sfx->Play();
}

void CCharSlotWidget::StopSFX()
{
    std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);
    sfx->Stop();
}