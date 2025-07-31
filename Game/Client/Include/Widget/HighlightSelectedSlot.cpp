#include "HighlightSelectedSlot.h"
#include "AllWidgets.h"

CHighlightSelectedSlot::CHighlightSelectedSlot()
{
	Construct();
}

CHighlightSelectedSlot::~CHighlightSelectedSlot()
{
}

void CHighlightSelectedSlot::Construct()
{
    GetTransform()->SetPivot(0.5f, 0.5f);

    CImage* highlight = CWidgetUtils::AllocateWidget<CImage>("HighlightSelectedSlot_Image");
    highlight->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
    highlight->GetTransform()->SetPivot(0.5f, 0.5f);
    highlight->SetTexture("Texture_UIAtlas");
    highlight->SetFrame("SelectHighlight");
    highlight->Set9SlicingCorner(FVector2D(10.0f, 10.0f));
    highlight->SetCornerRatio(2.0f);
    AddChild(highlight);
}

void CHighlightSelectedSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CHighlightSelectedSlot>(this);
}

void CHighlightSelectedSlot::SetSlot(CSlotWidget* slot)
{
    CTransform* slotTrans = slot->GetTransform();
    const FVector2D& slotWorldPos = slotTrans->GetWorldPos();
    const FVector2D& slotPivot = slotTrans->GetPivot();
    const FVector2D& slotScale = slotTrans->GetRelativeScale();

    FVector2D slotCenter = slotWorldPos - (slotScale * slotPivot) + (slotScale * 0.5f);

    GetTransform()->SetRelativeScale(slotScale * 1.1f);
    GetTransform()->SetWorldPos(slotCenter);
}