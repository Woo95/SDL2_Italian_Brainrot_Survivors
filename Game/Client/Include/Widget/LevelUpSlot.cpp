#include "LevelUpSlot.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/ItemDataManager.h"
#include "../Manager/EventManager.h"

CLevelUpSlot::CLevelUpSlot()
{
	Construct();
}

CLevelUpSlot::~CLevelUpSlot()
{
}

void CLevelUpSlot::Construct()
{
	SetInteractable(true);

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

	mStatus = CWidgetUtils::AllocateWidget<CTextBlock>("LevelUpSlot_TextBlock_New");
	mStatus->GetTransform()->SetRelativeScale(0.15f, 0.2f);
	mStatus->GetTransform()->SetRelativePos(0.7f, 0.125f);
	mStatus->SetAlignment(ETextBlock::Alignment::LEFT);
	mStatus->SetCharWidth(12.5f);
	mStatus->SetColor(255, 255, 0);
	mStatus->EnableShadow(true);
	mStatus->SetFont("Font64_CourierPrime_Regular");
	mStatus->SetText("New!");
	AddChild(mStatus);

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

	mItemIcon = CWidgetUtils::AllocateWidget<CImage>("LevelUpSlot_Image_WeaponIcon");
	mItemIcon->GetTransform()->SetRelativeScale(FVector2D(0.65f, 0.65f));
	mItemIcon->GetTransform()->SetPivot(0.5f, 0.5f);
	mItemIcon->SetTexture("Texture_ItemAtlas");
	mItemIcon->SetFrame("Empty");
	weaponBox->AddChild(mItemIcon);
}

void CLevelUpSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CLevelUpSlot>(this);
}

void CLevelUpSlot::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
	if (isReleased)
		CEventManager::GetInst()->Broadcast(EEventType::PLAYER_LEVEL_UP_SELECT, &mItem);
}

void CLevelUpSlot::UpdateSlot(const FSelectableItem& item)
{
	CItemDataManager* IDM = CGameDataManager::GetInst()->GetItemDataManager();
	switch (item.category)
	{
	case EItemCategory::POWERUP:
	{
		const FPowerUpData& powerUpData = IDM->GetPowerUpData((EPowerUpType)item.type);
		UpdateSlotData(powerUpData.name, powerUpData.description, powerUpData.name, item.level);
		break;
	}
	case EItemCategory::WEAPON:
	{
		const FWeaponData& weaponData = IDM->GetWeaponData((EWeaponType)item.type);
		UpdateSlotData(weaponData.name, weaponData.description, weaponData.name, item.level);
		break;
	}
	case EItemCategory::CONSUMABLE:
	{
		const FConsumableData& consumableData = IDM->GetConsumableData((EConsumableType)item.type);
		UpdateSlotData(consumableData.name, consumableData.description, consumableData.name, item.level);
		break;
	}
	default:
		break;
	}
	mItem = item;
}

void CLevelUpSlot::UpdateSlotData(const std::string& name, const std::string& description, const std::string& iconFrame, int level)
{
	mName->SetText(name);
	mDescription->SetText(description);
	mItemIcon->SetFrame(iconFrame);

	if (level == 0)
	{
		mStatus->SetColor(255, 255, 0);
		mStatus->EnableShadow(true);
		mStatus->SetText("New!");
	}
	else
	{
		mStatus->SetColor(255, 255, 255);
		mStatus->EnableShadow(false);
		mStatus->SetText("Level " + std::to_string(level));
	}
}