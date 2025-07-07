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

    mCharName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CharSlot");
    mCharName->GetTransform()->SetRelativeScale(0.9f, 0.175f);
    mCharName->GetTransform()->SetRelativePos(0.55f, 0.5f);
    mCharName->SetAlignment(ETextBlock::Alignment::LEFT);
    mCharName->SetCharWidth(12.5f);
    mCharName->SetFont("Font64_CourierPrime_Regular");
    AddChild(mCharName);
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

        if (mOnClickCallback)
            mOnClickCallback(this);
    }
}

void CCharSlotWidget::SetText(const std::string& name)
{
    mCharName->SetText(name);
    SetName(name);
}

void CCharSlotWidget::SetSFX(const std::string& sfx)
{
    mSFX = sfx;
}

void CCharSlotWidget::SetOnClick(std::function<void(CCharSlotWidget*)> callback)
{
    mOnClickCallback = callback;
}

void CCharSlotWidget::StopSFX()
{
    std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);
    sfx->Stop();
}