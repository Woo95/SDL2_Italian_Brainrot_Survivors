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
	int& level = mPowerUps[(int)type];

	// 등록된 파워업이 아닐 경우
	if (level == 0)
	{
		// 빈 슬롯이 없을 경우
		if (!HasEmptySlot(EItemCategory::POWERUP))
			return false;

		// 빈 슬롯이 있을 경우
		level++;
		mPowerUpCount++;
	}
	// 등록된 파워업이 맞을 경우
	else
	{
		// 등록된 파워업이 최대 레벨이 아닐 경우
		if (level < CONST_MAX_POWERUP_LEVEL)
			level++;
	}
	return true;
}

bool CInventoryComponent::AddWeapon(CWeapon* weapon)
{
	// 등록된 무기가 아닐 경우
	if (GetWeaponFromInventory(weapon->GetWeaponType()) == nullptr)
	{
		// 빈 슬롯이 없을 경우
		if (!HasEmptySlot(EItemCategory::WEAPON))
			return false;

		// 빈 슬롯이 있을 경우
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