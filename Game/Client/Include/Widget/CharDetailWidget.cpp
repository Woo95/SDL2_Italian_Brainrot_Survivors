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
    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("Image_CharSlot");
    panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("SelectSlot");
    panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
    panel->SetCornerRatio(1.5f);
    AddChild(panel);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_CharSlot");
    mName->GetTransform()->SetRelativeScale(0.97f, 0.19f);
    mName->GetTransform()->SetRelativePos(0.015f, 0.1f);
    mName->SetAlignment(ETextBlock::Alignment::LEFT);
    mName->SetCharWidth(12.5f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText(" ");
    AddChild(mName);
}

void CCharDetailWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CCharDetailWidget>(this);
}