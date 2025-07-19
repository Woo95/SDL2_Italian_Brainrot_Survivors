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
    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("Image_DetailPanel");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.5f);
    AddChild(panel);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailName");
    mName->GetTransform()->SetRelativeScale(0.97f, 0.19f);
    mName->GetTransform()->SetRelativePos(0.035f, 0.45f);
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText(" ");
    AddChild(mName);

    mDescription1 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailDescription1");
    mDescription1->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription1->GetTransform()->SetRelativePos(0.7f, 2.5f);
    mDescription1->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription1->SetCharWidth(12.5f);
    mDescription1->SetFont("Font64_CourierPrime_Regular");
    mDescription1->SetText(" ");
    AddChild(mDescription1);

    mDescription2 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailDescription2");
    mDescription2->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription2->GetTransform()->SetRelativePos(0.7f, 4.0f);
    mDescription2->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription2->SetCharWidth(12.5f);
    mDescription2->SetFont("Font64_CourierPrime_Regular");
    mDescription2->SetText(" ");
    AddChild(mDescription2);

    mCharacter = CWidgetUtils::AllocateWidget<CImage>("Image_DetailCharacter");
    mCharacter->GetTransform()->SetRelativeScale(FVector2D(0.12f, 0.55f));
    mCharacter->GetTransform()->SetRelativePos(0.07f, 2.0f);
    mCharacter->SetTexture("Texture_UIAtlas");
    mCharacter->SetFrame("Empty");
    AddChild(mCharacter);

    mWeaponBox = CWidgetUtils::AllocateWidget<CImage>("Image_DetailWeaponBox");
    mWeaponBox->GetTransform()->SetRelativeScale(FVector2D(0.1065f, 0.50f));
    mWeaponBox->GetTransform()->SetRelativePos(0.42f, 2.5f);
    mWeaponBox->SetTexture("Texture_UIAtlas");
    mWeaponBox->SetFrame("ItemBox");
    AddChild(mWeaponBox);
}

void CCharInfoWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharInfoWidget>(this);
}

void CCharInfoWidget::ShowDetail(CCharSlotWidget* slot)
{
    const std::string& key = slot->GetName();
    const FCharacterData& characterData = CGameDataManager::GetInst()->GetCharacterDataManager()->GetCharacterData(key);

    mName->SetText(characterData.firstName + " " + characterData.lastName);
    mDescription1->SetText(characterData.description1);
    mDescription2->SetText(characterData.description2);
}