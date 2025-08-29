#include "PlayerStatusComponent.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/PowerUpDataManager.h"
#include "../../Manager/Data/GameData/CharacterDataManager.h"
#include "../../Manager/Data/GameData/PlayerState.h"

CPlayerStatusComponent::CPlayerStatusComponent() :
	mPowerUpDataManager(nullptr),
	mPowerUpLevel({})
{
	mTypeID = typeid(CPlayerStatusComponent).hash_code();
}

CPlayerStatusComponent::~CPlayerStatusComponent()
{
}

bool CPlayerStatusComponent::Init()
{
	CGameDataManager* GDM = CGameDataManager::GetInst();

	CPlayerState* playerState = GDM->GetPlayerState();
	mPowerUpDataManager = GDM->GetPowerUpDataManager();

	/* Apply Base Status */
	{
		const FCharacterData& data =
			GDM->GetCharacterDataManager()->GetCharacterData(playerState->GetType());

		mBaseAttack      = data.baseAttack;
		mBaseDefense     = data.baseDefense;
		mBaseMaxHP       = data.baseMaxHp;
		mBaseAttackSpeed = data.baseAttackSpeed;
		mBaseMoveSpeed   = data.baseMoveSpeed;
		mBasePickupRange = data.basePickUpRange;
		mBaseGrowthExp   = data.baseGrowthExp;

		mHP = mBaseMaxHP;
	}

	/* Apply Menu PowerUps */
	{
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mPowerUpLevel[i] += playerState->GetPowerUpLvl((EPowerUpType)i);
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
	const float itemAttack = mBaseAttack * itemLevel * mightData.statModifier;

	return mBaseAttack + itemAttack;
}

float CPlayerStatusComponent::GetDefense() const
{
	const FPowerUpData& armorData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::ARMOR);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::ARMOR];
	const float itemArmor = itemLevel * armorData.statModifier;

	return mBaseDefense + itemArmor;
}

float CPlayerStatusComponent::GetMaxHP() const
{
	const FPowerUpData& maxHealthData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MAX_HEALTH);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MAX_HEALTH];
	const float itemMaxHP = mBaseMaxHP * itemLevel * maxHealthData.statModifier;

	return mBaseMaxHP + itemMaxHP;
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
	const float itemAttackSpeed = mBaseAttackSpeed * itemLevel * attackSpeedData.statModifier;

	return mBaseAttackSpeed + itemAttackSpeed;
}

float CPlayerStatusComponent::GetMoveSpeed() const
{
	const FPowerUpData& moveSpeedData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MOVE_SPEED);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MOVE_SPEED];
	const float itemMoveSpeed = mBaseMoveSpeed * itemLevel * moveSpeedData.statModifier;

	return mBaseMoveSpeed + itemMoveSpeed;
}

float CPlayerStatusComponent::GetPickupRange() const
{
	const FPowerUpData& pickupData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::MAGNET);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::MAGNET];
	const float itemPickupRange = mBasePickupRange * itemLevel * pickupData.statModifier;

	return mBasePickupRange + itemPickupRange;
}

float CPlayerStatusComponent::GetGrowthExp() const
{
	const FPowerUpData& growthData = mPowerUpDataManager->GetPowerUpData(EPowerUpType::GROWTH);

	const int itemLevel = mPowerUpLevel[(int)EPowerUpType::GROWTH];
	const float itemGrowth = itemLevel * growthData.statModifier;

	return mBaseGrowthExp + itemGrowth;
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

		mExpToLevelUp = (float)(2 * mLevel * mLevel + 10);
	}
}