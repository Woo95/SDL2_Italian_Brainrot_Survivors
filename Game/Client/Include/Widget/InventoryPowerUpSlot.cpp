#include "InventoryPowerUpSlot.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/ItemDataManager.h"

CInventoryPowerUpSlot::CInventoryPowerUpSlot()
{
	Construct();
}

CInventoryPowerUpSlot::~CInventoryPowerUpSlot()
{
}

void CInventoryPowerUpSlot::Construct()
{
	CImage* powerUpSlot = CWidgetUtils::AllocateWidget<CImage>("InventoryPowerUpSlot_Image_PowerUpSlot");
	powerUpSlot->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	powerUpSlot->GetTransform()->SetRelativePos(FVector2D(0.066f, 0.2505f));
	powerUpSlot->GetTransform()->SetPivot(0.5f, 0.5f);
	powerUpSlot->SetTexture("Texture_UIAtlas");
	powerUpSlot->SetFrame("PowerUpSlot");
	AddChild(powerUpSlot);

	mItemIcon = CWidgetUtils::AllocateWidget<CImage>("InventoryPowerUpSlot_Image_PowerUpIcon");
	mItemIcon->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	mItemIcon->GetTransform()->SetPivot(0.5f, 0.5f);
	mItemIcon->SetTexture("Texture_ItemAtlas");
	mItemIcon->SetFrame("Empty");
	powerUpSlot->AddChild(mItemIcon);
}

void CInventoryPowerUpSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInventoryPowerUpSlot>(this);
}

void CInventoryPowerUpSlot::UpdateSlot(EPowerUpType type)
{
	const FPowerUpData& powerUpData = CGameDataManager::GetInst()->GetItemDataManager()->GetPowerUpData(type);

	mItemIcon->SetFrame(powerUpData.name);
}
