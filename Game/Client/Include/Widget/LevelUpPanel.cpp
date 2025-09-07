#include "LevelUpPanel.h"
#include "AllWidgets.h"

CLevelUpPanel::CLevelUpPanel()
{
	Construct();
}

CLevelUpPanel::~CLevelUpPanel()
{
}

void CLevelUpPanel::Construct()
{
	SetInteractable(true);

	CImage* panel = CWidgetUtils::AllocateWidget<CImage>("LevelUpPanel_Image_Panel");
	panel->GetTransform()->SetRelativeScale(FVector2D(0.4f, 0.8f));
	panel->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.075f));
	panel->GetTransform()->SetPivot(FVector2D(0.5f, 0.0f));
	panel->SetTexture("Texture_UIAtlas");
	panel->SetFrame("PanelBox");
	panel->Set9SlicingCorner(FVector2D(15.f, 15.f));
	panel->SetCornerRatio(1.25f);
	AddChild(panel);

	CTextBlock* category = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpPanel_TextBlock_Category");
	category->GetTransform()->SetRelativeScale(panel->GetTransform()->GetRelativeScale() * FVector2D(0.45f, 0.07f));
	category->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.11f));
	category->GetTransform()->SetPivot(FVector2D(0.5f, 0.0f));
	category->SetAlignment(ETextBlock::Alignment::CENTER);
	category->SetCharWidth(50.f);
	category->SetFont("Font64_CourierPrime_Regular");
	category->SetText("Level Up!");
	AddChild(category);

	CTextBlock* guide = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpPanel_TextBlock_Guide");
	guide->GetTransform()->SetRelativeScale(panel->GetTransform()->GetRelativeScale() * FVector2D(0.85f, 0.05f));
	guide->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.75f));
	guide->GetTransform()->SetPivot(FVector2D(0.5f, 0.0f));
	guide->SetAlignment(ETextBlock::Alignment::CENTER);
	guide->SetCharWidth(50.f);
	guide->SetFont("Font64_CourierPrime_Regular");
	guide->SetText("Please select one of the choices above.");
	AddChild(guide);

	///// Slot-Related Code - BEGIN /////
	const FVector2D slotScale = FVector2D(0.38f, 0.16f);
	const FVector2D slotStartPos = FVector2D(panel->GetTransform()->GetRelativePos().x - slotScale.x * 0.5f, 0.2f);
	for (int i = 0; i < 3; i++)
	{
		mSlots[i] = CreateLevelUpSlot(i, slotScale, slotStartPos + FVector2D(0.0f, slotScale.y * i * 1.03f));
	}
}

void CLevelUpPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CLevelUpPanel>(this);
}

CLevelUpSlot* CLevelUpPanel::CreateLevelUpSlot(int idx, const FVector2D& scale, const FVector2D& pos)
{
	CLevelUpSlot* slot = CWidgetUtils::AllocateWidget<CLevelUpSlot, 4>("LevelUpPanel_LevelUpSlot_" + idx);

	slot->GetTransform()->SetRelativeScale(scale);
	slot->GetTransform()->SetRelativePos(pos);
	AddChild(slot);

	return slot;
}

const FVector2D CLevelUpPanel::CalcSlotPos(int col, int row) const
{
	const FVector2D slotScale = FVector2D(0.38f, 0.16f);
	const float offsetX = slotScale.x;
	const float offsetY = slotScale.y * 1.05f;

	return FVector2D(offsetX * col, offsetY * row);
}