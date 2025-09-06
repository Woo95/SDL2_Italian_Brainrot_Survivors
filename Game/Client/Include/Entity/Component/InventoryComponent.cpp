#include "InventoryComponent.h"

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

bool CInventoryComponent::Init()
{
	// 최초 시작시 플레이어의 시작무기를 가져와야함.

	return true;
}

void CInventoryComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInventoryComponent>(this);
}

bool CInventoryComponent::AddPowerUp(EPowerUpType type)
{
	int idx = (int)type;

	// 이미 최대 레벨일 경우
	if (mPowerUps[idx] >= CONST_MAX_POWERUP_LEVEL)
		return false;

	if (mPowerUps[idx] == 0)
	{
		// 빈 슬롯이 없을 경우
		if (mPowerUpCount >= CONST_MAX_POWERUP_SLOT)
			return false;

		// 빈 슬롯이 있을 경우
		mPowerUpCount++;
	}
	mPowerUps[idx]++;

	return true;
}

bool CInventoryComponent::AddWeapon(EWeaponType type)
{
	int idx = (int)type;

	// 이미 최대 레벨일 경우
	if (mWeapons[idx] >= CONST_MAX_WEAPON_LEVEL)
		return false;

	if (mWeapons[idx] == 0)
	{
		// 빈 슬롯이 없을 경우
		if (mWeaponCount >= CONST_MAX_WEAPON_SLOT)
			return false;

		// 빈 슬롯이 있을 경우
		mWeaponCount++;
	}
	mWeapons[idx]++;

	return true;
}