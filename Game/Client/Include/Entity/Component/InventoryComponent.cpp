#include "InventoryComponent.h"
#include "../Object/Weapon.h"

CInventoryComponent::CInventoryComponent() :
	mPowerUps({}),
	mPowerUpCount(0),
	mWeapons({}),
	mWeaponCount(0)
{
	mTypeID = typeid(CInventoryComponent).hash_code();
}

CInventoryComponent::~CInventoryComponent()
{
}

void CInventoryComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInventoryComponent>(this);
}

bool CInventoryComponent::AddPowerUp(EPowerUpType type)
{
	// 빈 슬롯이 없을 경우
	if (!HasEmptySlot(EItemCategory::POWERUP))
		return false;

	// 등록된 파워업이 아닐 경우
	if (GetPowerUpFromInventory(type) == 0)
	{
		mPowerUps[(int)type]++;
		mPowerUpCount++;
	}
	else
	{
		// 최대 레벨이 아닐 경우
		if (mPowerUps[(int)type] < CONST_MAX_POWERUP_LEVEL)
			mPowerUps[(int)type]++;
	}
	return true;
}

bool CInventoryComponent::AddWeapon(CWeapon* weapon)
{
	// 빈 슬롯이 없을 경우
	if (!HasEmptySlot(EItemCategory::WEAPON))
		return false;

	// 등록된 무기가 아닐 경우
	if (GetWeaponFromInventory(weapon->GetWeaponType()) == nullptr)
	{
		mWeapons[mWeaponCount] = weapon;
		mWeaponCount++;
	}
	weapon->AddWeaponLevel();

	return true;
}

CWeapon* CInventoryComponent::GetWeaponFromInventory(EWeaponType type) const
{
	for (int i = 0; i < mWeaponCount; i++)
	{
		if (mWeapons[i]->GetWeaponType() == type)
			return mWeapons[i];
	}
	return nullptr;
}

int CInventoryComponent::GetWeaponLevel(EWeaponType type) const
{
	if (CWeapon* weapon = GetWeaponFromInventory(type))
	{
		return weapon->GetWeaponLevel();
	}
	return 0;
}