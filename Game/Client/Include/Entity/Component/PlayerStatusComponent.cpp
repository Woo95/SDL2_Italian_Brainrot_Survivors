#include "PlayerStatusComponent.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/PlayerProfile.h"
#include "../../Manager/Data/GameData/CharacterDataManager.h"
#include "../../Manager/Data/GameData/PowerUpDataManager.h"

CPlayerStatusComponent::CPlayerStatusComponent()
{
	mTypeID = typeid(CPlayerStatusComponent).hash_code();
}

CPlayerStatusComponent::~CPlayerStatusComponent()
{
}

bool CPlayerStatusComponent::Init()
{
	CComponent::Init();

	CGameDataManager* GDM = CGameDataManager::GetInst();
	CPlayerProfile* profile = GDM->GetPlayerProfile();
	CCharacterDataManager* CDM = GDM->GetCharacterDataManager();
	CPowerUpDataManager* PDM = GDM->GetPowerUpDataManager();

	/* Apply Base Status */
	{
		const FCharacterData& data = CDM->GetCharacterData(profile->GetType());

		mBaseAttack      = data.baseAttack;
		mBaseDefense     = data.baseDefense;
		mBaseMaxHP       = data.baseMaxHp;
		mBaseAttackSpeed = data.baseAttackSpeed;
		mBaseMoveSpeed   = data.baseMoveSpeed;
		mBasePickupRange = data.basePickUpRange;
		mBaseGrowthExp   = data.baseGrowthExp;

		mHP = mBaseMaxHP;
	}

	/* Apply PowerUp Stat Modifiers */
	{
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mPowerUpModifiers[i] = PDM->GetPowerUpData((EPowerUpType)i).statModifier;
	}

	return true;
}

void CPlayerStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPlayerStatusComponent>(this);
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