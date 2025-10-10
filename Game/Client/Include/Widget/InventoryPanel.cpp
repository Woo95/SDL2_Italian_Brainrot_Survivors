#include "InventoryPanel.h"
#include "AllWidgets.h"

CInventoryPanel::CInventoryPanel()
{
	Construct();
}

CInventoryPanel::~CInventoryPanel()
{

}

void CInventoryPanel::Construct()
{
	const FVector2D slotScale = FVector2D(0.1561f, 0.4565f);
	FVector2D slotStartPos = FVector2D(-0.5f + slotScale.x * 0.5f, -0.5f + slotScale.y * 0.5f);

	const float totalSlotWidth = slotScale.x * CONST_WIDGET_MAX_WEAPON_SLOT;
	const float gap = (1.0f - totalSlotWidth) / (CONST_WIDGET_MAX_WEAPON_SLOT - 0.75f);

	for (int i = 0; i < CONST_WIDGET_MAX_WEAPON_SLOT; i++)
	{
		FVector2D slotPos = slotStartPos + FVector2D(i * (slotScale.x + gap), 0.0f);
		mWeaponSlots[i] = CreateWeaponSlot(i, slotScale, slotPos);

		if (i >= CONST_MAX_WEAPON_SLOT)
			mWeaponSlots[i]->NotUsingSlot();
	}

	slotStartPos = FVector2D(-0.5f + slotScale.x * 0.5f, 0.052f + slotScale.y * 0.5f);
	for (int i = 0; i < CONST_WIDGET_MAX_POWERUP_SLOT; i++)
	{
		FVector2D slotPos = slotStartPos + FVector2D(i * (slotScale.x + gap), 0.0f);
		mPowerUpSlots[i] = CreatePowerUpSlot(i, slotScale, slotPos);
	}
}

void CInventoryPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInventoryPanel>(this);
}

void CInventoryPanel::AddWeapon(EWeaponType type)
{
	if (mWeaponCount >= CONST_WIDGET_MAX_WEAPON_SLOT)
		return;

	mWeaponSlots[mWeaponCount]->UpdateSlot(type);
	mWeaponCount++;
}

void CInventoryPanel::AddPowerUp(EPowerUpType type)
{
	if (mPowerUpCount >= CONST_WIDGET_MAX_POWERUP_SLOT)
		return;

	mPowerUpSlots[mPowerUpCount]->UpdateSlot(type);
	mPowerUpCount++;
}

CInventoryWeaponSlot* CInventoryPanel::CreateWeaponSlot(int idx, const FVector2D& scale, const FVector2D& pos)
{
	CInventoryWeaponSlot* slot = CWidgetUtils::AllocateWidget<CInventoryWeaponSlot, CONST_WIDGET_MAX_WEAPON_SLOT>("InventoryPanel_WeaponSlot_" + idx);

	slot->GetTransform()->SetRelativeScale(scale);
	slot->GetTransform()->SetRelativePos(pos);
	slot->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(slot);

	return slot;
}

CInventoryPowerUpSlot* CInventoryPanel::CreatePowerUpSlot(int idx, const FVector2D& scale, const FVector2D& pos)
{
	CInventoryPowerUpSlot* slot = CWidgetUtils::AllocateWidget<CInventoryPowerUpSlot, CONST_WIDGET_MAX_POWERUP_SLOT>("InventoryPanel_PowerUpSlot_" + idx);

	slot->GetTransform()->SetRelativeScale(scale);
	slot->GetTransform()->SetRelativePos(pos);
	slot->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(slot);

	return slot;
}
