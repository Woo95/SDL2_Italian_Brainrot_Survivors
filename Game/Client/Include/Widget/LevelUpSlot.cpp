#include "LevelUpSlot.h"
#include "AllWidgets.h"

CLevelUpSlot::CLevelUpSlot()
{
	Construct();
}

CLevelUpSlot::~CLevelUpSlot()
{
}

void CLevelUpSlot::Construct()
{
	CImage* panel = CWidgetUtils::AllocateWidget<CImage>("LevelUpSlot_Image_Panel");
	panel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	panel->SetTexture("Texture_UIAtlas");
	panel->SetFrame("SelectSlotBox");
	panel->Set9SlicingCorner(FVector2D(6.0f, 6.0f));
	panel->SetCornerRatio(1.5f);
	AddChild(panel);

	mName = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpSlot_TextBlock_Name");
	mName->GetTransform()->SetRelativeScale(0.2f, 0.2f);
	mName->GetTransform()->SetRelativePos(0.2f, 0.125f);
	mName->SetAlignment(ETextBlock::Alignment::LEFT);
	mName->SetCharWidth(12.5f);
	mName->SetFont("Font64_CourierPrime_Regular");
	mName->SetText("NAME");
	AddChild(mName);

	mNew = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpSlot_TextBlock_New");
	mNew->GetTransform()->SetRelativeScale(0.1f, 0.2f);
	mNew->GetTransform()->SetRelativePos(0.7f, 0.125f);
	mNew->SetAlignment(ETextBlock::Alignment::LEFT);
	mNew->SetCharWidth(12.5f);
	mNew->SetColor(255, 255, 0);
	mNew->EnableShadow(true);
	mNew->SetFont("Font64_CourierPrime_Regular");
	mNew->SetText("New!");
	AddChild(mNew);

	mDescription = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpSlot_TextBlock_Desc");
	mDescription->GetTransform()->SetRelativeScale(0.9f, 0.2f);
	mDescription->GetTransform()->SetRelativePos(0.05f, 0.6f);
	mDescription->SetAlignment(ETextBlock::Alignment::LEFT);
	mDescription->SetCharWidth(12.5f);
	mDescription->SetFont("Font64_CourierPrime_Regular");
	mDescription->SetText("DESCRIPTION DESCRIPTION DESCRIPTION DESCRIPTION");
	AddChild(mDescription);

	CImage* weaponBox = CWidgetUtils::AllocateWidget<CImage>("LevelUpSlot_Image_WeaponBox");
	weaponBox->GetTransform()->SetRelativeScale(FVector2D(0.11f, 0.41f));
	weaponBox->GetTransform()->SetRelativePos(0.066f, 0.2505f);
	weaponBox->GetTransform()->SetPivot(0.5f, 0.5f);
	weaponBox->SetTexture("Texture_UIAtlas");
	weaponBox->SetFrame("WeaponBox");
	AddChild(weaponBox);

	mWeaponIcon = CWidgetUtils::AllocateWidget<CImage>("LevelUpSlot_Image_WeaponIcon");
	mWeaponIcon->GetTransform()->SetRelativeScale(FVector2D(0.65f, 0.65f));
	mWeaponIcon->GetTransform()->SetPivot(0.5f, 0.5f);
	mWeaponIcon->SetTexture("Texture_ItemAtlas");
	mWeaponIcon->SetFrame("Empty");
	weaponBox->AddChild(mWeaponIcon);
}

void CLevelUpSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CLevelUpSlot>(this);
}