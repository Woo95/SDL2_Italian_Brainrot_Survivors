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

	/* 초기 스탯 저장 */
	{
		const FCharacterData& data = CDM->GetCharacterData(profile->GetType());

		mBaseAttack      = data.baseAttack;
		mBaseDefense     = data.baseDefense;
		mBaseMaxHP       = data.baseMaxHp;
		mBaseAttackSpeed = data.baseAttackSpeed;
		mBaseMoveSpeed   = data.baseMoveSpeed;
		mBasePickupRange = data.basePickUpRange;
		mBaseGrowthExp   = data.baseGrowthExp;
	}

	/* 파워업 관련 */
	{
		/* 메뉴에서 구매한 파워업 저장 */
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mMenuPowerUps[i] = profile->GetMenuPowerUpLvl((EPowerUpType)i);

		/* 파워업 레벨업 당 증가비율 저장 */
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mPowerUpModifiers[i] = PDM->GetPowerUpData((EPowerUpType)i).statModifier;
	}

	// 초기 체력 설정
	mMaxHP = mBaseMaxHP + mMenuPowerUps[(int)EPowerUpType::MAX_HEALTH] * mPowerUpModifiers[(int)EPowerUpType::MAX_HEALTH];
	mHP = mMaxHP;

	return true;
}

void CPlayerStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPlayerStatusComponent>(this);
}