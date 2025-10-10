#include "InventoryWeaponSlot.h"
#include "AllWidgets.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/ItemDataManager.h"

CInventoryWeaponSlot::CInventoryWeaponSlot()
{
	Construct();
}

CInventoryWeaponSlot::~CInventoryWeaponSlot()
{
}

void CInventoryWeaponSlot::Construct()
{
	CImage* weaponSlot = CWidgetUtils::AllocateWidget<CImage>("InventoryWeaponSlot_Image_WeaponSlot");
	weaponSlot->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	weaponSlot->GetTransform()->SetRelativePos(FVector2D(0.066f, 0.2505f));
	weaponSlot->GetTransform()->SetPivot(0.5f, 0.5f);
	weaponSlot->SetTexture("Texture_UIAtlas");
	weaponSlot->SetFrame("WeaponSlot");
	AddChild(weaponSlot);

	mItemIcon = CWidgetUtils::AllocateWidget<CImage>("InventoryWeaponSlot_Image_WeaponIcon");
	mItemIcon->GetTransform()->SetRelativeScale(FVector2D(1.0f, 1.0f));
	mItemIcon->GetTransform()->SetPivot(0.5f, 0.5f);
	mItemIcon->SetTexture("Texture_ItemAtlas");
	mItemIcon->SetFrame("Empty");
	weaponSlot->AddChild(mItemIcon);
}

void CInventoryWeaponSlot::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInventoryWeaponSlot>(this);
}

void CInventoryWeaponSlot::UpdateSlot(EWeaponType type)
{
	const FWeaponData& weaponData = CGameDataManager::GetInst()->GetItemDataManager()->GetWeaponData(type);

	mItemIcon->SetFrame(weaponData.name);
}

void CInventoryWeaponSlot::NotUsingSlot()
{
	mItemIcon->SetFrame("XSymbol");
	mItemIcon->SetAlpha(125.0f);
}