#include "HighlightSelectedSlotWidget.h"
#include "AllWidgets.h"

CHighlightSelectedSlotWidget::CHighlightSelectedSlotWidget()
{
	Construct();
}

CHighlightSelectedSlotWidget::~CHighlightSelectedSlotWidget()
{
}

void CHighlightSelectedSlotWidget::Construct()
{
    GetTransform()->SetPivot(0.5f, 0.5f);

    CImage* highlight = CWidgetUtils::AllocateWidget<CImage>("Image_SelectHighlight");
    highlight->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    highlight->GetTransform()->SetPivot(0.5f, 0.5f);
    highlight->SetTexture("Texture_UIAtlas");
    highlight->SetFrame("SelectHighlight");
    highlight->Set9SlicingCorner(FVector2D(10.0f, 10.0f));
    highlight->SetCornerRatio(2.0f);
    AddChild(highlight);
}

void CHighlightSelectedSlotWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CHighlightSelectedSlotWidget>(this);
}

void CHighlightSelectedSlotWidget::SetSlot(CSlotWidget* slot)
{
    CTransform* slotTrans = slot->GetTransform();
    const FVector2D& slotWorldPos = slotTrans->GetWorldPos();
    const FVector2D& slotPivot = slotTrans->GetPivot();
    const FVector2D& slotScale = slotTrans->GetRelativeScale();

    FVector2D slotCenter = slotWorldPos - (slotScale * slotPivot) + (slotScale * 0.5f);

    GetTransform()->SetRelativeScale(slotScale * 1.1f);
    GetTransform()->SetWorldPos(slotCenter);
}