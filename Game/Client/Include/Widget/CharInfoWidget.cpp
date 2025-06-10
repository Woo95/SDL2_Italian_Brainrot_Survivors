#include "CharInfoWidget.h"
#include "AllWidgets.h"
#include "../Manager/GameData/GameDataManager.h"
#include "../Manager/GameData/InfoManager.h"

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
    mName->GetTransform()->SetRelativePos(0.015f, 0.1f);
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText(" ");
    AddChild(mName);

    mDescription1 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailDescription1");
    mDescription1->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription1->GetTransform()->SetRelativePos(0.28f, 0.35f);
    mDescription1->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription1->SetCharWidth(12.5f);
    mDescription1->SetFont("Font64_CourierPrime_Regular");
    mDescription1->SetText(" ");
    AddChild(mDescription1);

    mDescription2 = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailDescription2");
    mDescription2->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription2->GetTransform()->SetRelativePos(0.28f, 0.55f);
    mDescription2->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription2->SetCharWidth(12.5f);
    mDescription2->SetFont("Font64_CourierPrime_Regular");
    mDescription2->SetText(" ");
    AddChild(mDescription2);

    mCharacter = CWidgetUtils::AllocateWidget<CImage>("Image_DetailCharacter");
    mCharacter->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.55f));
    mCharacter->GetTransform()->SetRelativePos(0.025f, 0.35f);
    mCharacter->SetTexture("Texture_UIAtlas");
    mCharacter->SetFrame("Empty");
    AddChild(mCharacter);

    mWeaponBox = CWidgetUtils::AllocateWidget<CImage>("Image_DetailWeaponBox");
    mWeaponBox->GetTransform()->SetRelativeScale(FVector2D(0.1065f, 0.50f));
    mWeaponBox->GetTransform()->SetRelativePos(0.15f, 0.40f);
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
    const FCharacterInfo* characterInfo = CGameDataManager::GetInst()->GetInfoManager()->GetCharacterInfo(key);

    mName->SetText(characterInfo->name);
    mDescription1->SetText(characterInfo->description1);
    mDescription2->SetText(characterInfo->description2);
}