#include "PlayerStatusComponent.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/PowerUpDataManager.h"
#include "../../Manager/Data/GameData/PlayerState.h"

CPlayerStatusComponent::CPlayerStatusComponent() :
	mPowerUpDataManager(nullptr),
	mPowerUpLevel({}),
	mLevelUpNotifyCount(0)
{
	mTypeID = typeid(CPlayerStatusComponent).hash_code();
}

CPlayerStatusComponent::~CPlayerStatusComponent()
{

}

bool CPlayerStatusComponent::Init()
{
	mPowerUpDataManager = CGameDataManager::GetInst()->GetPowerUpDataManager();

	// Apply power-ups from menu purchases
	CPlayerState* playerState = CGameDataManager::GetInst()->GetPlayerState();
	for (int i = 0; i < (int)EPowerUpType::MAX; i++)
	{
		const EPowerUpType& type = static_cast<EPowerUpType>(i);
		mPowerUpLevel[i] += playerState->GetOwnedPowerUpCount(type);
	}

	return CComponent::Init();
}

void CPlayerStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPlayerStatusComponent>(this);
}

float CPlayerStatusComponent::GetAttack() const
{
	const FPowerUpData& mightData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MIGHT);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MIGHT];
	const float itemAttack = mRawAttack * itemLevel * mightData.statModifier;

	return mRawAttack + itemAttack;
}

float CPlayerStatusComponent::GetDefense() const
{
	const FPowerUpData& armorData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::ARMOR);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::ARMOR];
	const float itemArmor = itemLevel * armorData.statModifier;

	return mRawDefense + itemArmor;
}

float CPlayerStatusComponent::GetMaxHP() const
{
	const FPowerUpData& maxHealthData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MAX_HEALTH);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MAX_HEALTH];
	const float itemMaxHP = mRawMaxHP + itemLevel * maxHealthData.statModifier;

	return mRawMaxHP + itemMaxHP;
}

float CPlayerStatusComponent::GetRecoveryHP() const
{
	const FPowerUpData& recoveryData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::RECOVERY);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::RECOVERY];
	const float itemRecovery = itemLevel * recoveryData.statModifier;

	return itemRecovery;
}

float CPlayerStatusComponent::GetAttackSpeed() const
{
	const FPowerUpData& attackSpeedData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::ATTACK_SPEED);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::ATTACK_SPEED];
	const float itemAttackSpeed = mRawAttackSpeed * itemLevel * attackSpeedData.statModifier;

	return mRawAttackSpeed + itemAttackSpeed;
}

float CPlayerStatusComponent::GetMoveSpeed() const
{
	const FPowerUpData& moveSpeedData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MOVE_SPEED);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MOVE_SPEED];
	const float itemMoveSpeed = mRawMoveSpeed * itemLevel * moveSpeedData.statModifier;

	return mRawMoveSpeed + itemMoveSpeed;
}

float CPlayerStatusComponent::GetPickupRange() const
{
	const FPowerUpData& pickupData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MAGNET);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MAGNET];
	const float itemPickupRange = mRawPickupRange * itemLevel * pickupData.statModifier;

	return mRawPickupRange + itemPickupRange;
}

int CPlayerStatusComponent::PopLevelUpNotify()
{
	const int returnVal = mLevelUpNotifyCount;
	mLevelUpNotifyCount = 0;

	return returnVal;
}

void CPlayerStatusComponent::AddExp(float exp)
{
	mExp += exp;

	while (mExp >= mExpToLevelUp)
	{
		mLevel++;
		mLevelUpNotifyCount++;
		mExp -= mExpToLevelUp;

		mExpToLevelUp = 2 * mLevel * mLevel + 10;
	}
}