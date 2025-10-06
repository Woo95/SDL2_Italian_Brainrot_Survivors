#include "InventoryComponent.h"
#include "WeaponComponent.h"

CInventoryComponent::CInventoryComponent()
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

void CInventoryComponent::AddPowerUp(EPowerUpType type)
{
	// 등록된 파워업이 아닐 경우
	if (!GetPowerUp(type))
	{
		// 빈 슬롯이 없을 경우
		if (!HasEmptySlot(EItemCategory::POWERUP))
			return;

		// 빈 슬롯이 있을 경우
		mPowerUps[mPowerUpCount].type = type;
		mPowerUps[mPowerUpCount].level = 0;
		mPowerUpCount++;
	}

	if (GetPowerUpLevel(type) < CONST_MAX_POWERUP_LEVEL)
		GetPowerUp(type)->level++;
}

void CInventoryComponent::AddWeapon(EWeaponType type, CWeaponComponent* weapon)
{
	// 등록된 무기가 아닐 경우
	if (!GetWeapon(type))
	{
		// 빈 슬롯이 없을 경우
		if (!HasEmptySlot(EItemCategory::WEAPON))
			return;

		// 빈 슬롯이 있을 경우
		mWeapons[mWeaponCount].ptr = weapon;
		mWeaponCount++;
	}
	weapon->Upgrade();
}

FPowerUp* CInventoryComponent::GetPowerUp(EPowerUpType type)
{
	for (int i = 0; i < mPowerUpCount; i++)
	{
		if (mPowerUps[i].type == type)
			return &mPowerUps[i];
	}
	return nullptr;
}

FWeapon* CInventoryComponent::GetWeapon(EWeaponType type)
{
	for (int i = 0; i < mWeaponCount; i++)
	{
		if (mWeapons[i].ptr->GetType() == type)
			return &mWeapons[i];
	}
	return nullptr;
}

int CInventoryComponent::GetPowerUpLevel(EPowerUpType type)
{
	if (FPowerUp* powerUp = GetPowerUp(type))
	{
		return powerUp->level;
	}
	return 0;
}

int CInventoryComponent::GetWeaponLevel(EWeaponType type)
{
	if (FWeapon* weapon = GetWeapon(type))
	{
		return weapon->ptr->GetLevel();
	}
	return 0;
}