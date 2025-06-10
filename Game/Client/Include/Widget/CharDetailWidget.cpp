#include "CharDetailWidget.h"
#include "AllWidgets.h"

CCharDetailWidget::CCharDetailWidget()
{
    Construct();
}

CCharDetailWidget::~CCharDetailWidget()
{
}

void CCharDetailWidget::Construct()
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

    mDescription = CWidgetUtils::AllocateWidget<CTextBlock>("Text_DetailDescription");
    mDescription->GetTransform()->SetRelativeScale(0.65f, 0.19f);
    mDescription->GetTransform()->SetRelativePos(0.28f, 0.35f);
    mDescription->SetAlignment(ETextBlock::Alignment::LEFT);
    mDescription->SetCharWidth(12.5f);
    mDescription->SetFont("Font64_CourierPrime_Regular");
    mDescription->SetText(" ");
    AddChild(mDescription);

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

void CCharDetailWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharDetailWidget>(this);
}

void CCharDetailWidget::ShowDetail(CSlotWidget* slot)
{
    // todo
}