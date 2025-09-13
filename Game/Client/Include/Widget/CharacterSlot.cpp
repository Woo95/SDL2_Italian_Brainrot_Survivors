#include "CharacterSlot.h"
#include "AllWidgets.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CCharacterSlot::CCharacterSlot()
{
	Construct();
}

CCharacterSlot::~CCharacterSlot()
{
}

void CCharacterSlot::Construct()
{
    SetInteractable(true);

    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("CharSlot_Image_Panel");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->GetTransform()->SetPivot(0.5f, 0.5f);
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlotBox");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.25f);
    AddChild(panel);

    mNameText = CWidgetUtils::AllocateWidget<CTextBlock>("CharSlot_TextBlock_Name");
    mNameText->GetTransform()->SetRelativeScale(0.9f, 0.175f);
    mNameText->GetTransform()->SetPivot(0.5f, 2.4f);
    mNameText->SetAlignment(ETextBlock::Alignment::LEFT);
    mNameText->SetCharWidth(12.5f);
    mNameText->SetFont("Font64_CourierPrime_Regular");
    panel->AddChild(mNameText);

    mCharacter = CWidgetUtils::AllocateWidget<CAnimatedImage, 3>("CharSlot_AnimatedImage_Character");
    mCharacter->SetAnimating(false);
    panel->AddChild(mCharacter);

    mWeaponIcon = CWidgetUtils::AllocateWidget<CImage>("CharSlot_Image_Weapon");
    mWeaponIcon->GetTransform()->SetRelativeScale(0.3f, 0.3f);
    mWeaponIcon->GetTransform()->SetRelativePos(13.0f, 4.0f);
    mWeaponIcon->SetTexture("Texture_ItemAtlas");
    panel->AddChild(mWeaponIcon);
}

void CCharacterSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CCharacterSlot>(this);
}

void CCharacterSlot::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (isPressed)
    {
        CCharacterSelectPanel* panel = static_cast<CCharacterSelectPanel*>(mParent);
        panel->OnSlotClicked(this);
    }
}

void CCharacterSlot::PlaySFX()
{
    std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);

    if (!sfx->IsPlaying())
        sfx->Play();
}

void CCharacterSlot::StopSFX()
{
    std::shared_ptr<CSFX> sfx = CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>(mSFX);
    sfx->Stop();
}