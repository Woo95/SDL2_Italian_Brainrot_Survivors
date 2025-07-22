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
    CImage* highlight = CWidgetUtils::AllocateWidget<CImage>("Image_SelectHighlight");
    highlight->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
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
    const FVector2D& slotCenter =  slot->GetTransform()->GetRelativePos() - (GetTransform()->GetWorldScale() - slot->GetTransform()->GetWorldScale()) * 0.5f;
    GetTransform()->SetRelativePos(slotCenter);
}