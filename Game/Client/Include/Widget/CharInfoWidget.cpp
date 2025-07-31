#include "CharInfoWidget.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/CharacterDataManager.h"

CCharInfoWidget::CCharInfoWidget()
{
    Construct();
}

CCharInfoWidget::~CCharInfoWidget()
{
}

void CCharInfoWidget::Construct()
{
    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("Image_InfoPanel");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.5f);
    AddChild(panel);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_InfoName");
    mName->GetTransform()->SetRelativeScale(0.97f, 0.19f);
    mName->GetTransform()->SetRelativePos(0.035f, 0.45f);
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText(" ");
    AddChild(mName);

    mDescription1 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_InfoDescription1");
    mDescription1->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription1->GetTransform()->SetRelativePos(0.7f, 2.5f);
    mDescription1->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription1->SetCharWidth(12.5f);
    mDescription1->SetFont("Font64_CourierPrime_Regular");
    mDescription1->SetText(" ");
    AddChild(mDescription1);

    mDescription2 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_InfoDescription2");
    mDescription2->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription2->GetTransform()->SetRelativePos(0.7f, 4.0f);
    mDescription2->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription2->SetCharWidth(12.5f);
    mDescription2->SetFont("Font64_CourierPrime_Regular");
    mDescription2->SetText(" ");
    AddChild(mDescription2);

    mCharacter = CWidgetUtils::AllocateWidget<CImage>("Image_InfoCharacter");
    mCharacter->GetTransform()->SetRelativePos(0.035f, 5.85f);
    mCharacter->GetTransform()->SetPivot(0.0f, 1.0f);
    AddChild(mCharacter);

    CImage* weaponBox = CWidgetUtils::AllocateWidget<CImage>("Image_InfoWeaponBox");
    weaponBox->GetTransform()->SetRelativeScale(FVector2D(0.1065f, 0.5f));
    weaponBox->GetTransform()->SetRelativePos(0.5f, 4.1f);
    weaponBox->GetTransform()->SetPivot(0.5f, 0.5f);
    weaponBox->SetTexture("Texture_UIAtlas");
    weaponBox->SetFrame("WeaponBox");
    AddChild(weaponBox);

    mWeaponIcon = CWidgetUtils::AllocateWidget<CImage>("Image_InfoPowerUpIcon");
    mWeaponIcon->GetTransform()->SetRelativeScale(FVector2D(0.65f, 0.65f));
    mWeaponIcon->GetTransform()->SetPivot(0.5f, 0.5f);
    mWeaponIcon->SetTexture("Texture_ItemAtlas");
    mWeaponIcon->SetFrame("Empty");
    weaponBox->AddChild(mWeaponIcon);
}

void CCharInfoWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharInfoWidget>(this);
}

void CCharInfoWidget::ShowInfo(CCharacterSlot* slot)
{
    const FCharacterData& characterData = CGameDataManager::GetInst()->GetCharacterDataManager()->GetCharacterData(slot->GetType());

    mName->SetText(characterData.firstName + " " + characterData.lastName);
    mDescription1->SetText(characterData.description1);
    mDescription2->SetText(characterData.description2);
    mWeaponIcon->SetFrame(characterData.startingWeapon);
    mCharacter->SetTexture("Texture_" + characterData.lastName);
    mCharacter->SetFrame(characterData.lastName);
    mCharacter->GetTransform()->SetWorldScale(slot->GetAnimatedImage()->GetTransform()->GetWorldScale());
}