#include "PlayerStatusComponent.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/PlayerProfile.h"
#include "../../Manager/Data/GameData/CharacterDataManager.h"
#include "../../Manager/Data/GameData/ItemDataManager.h"
#include "../../Manager/EventManager.h"

CPlayerStatusComponent::CPlayerStatusComponent()
{
	mTypeID = typeid(CPlayerStatusComponent).hash_code();
}

CPlayerStatusComponent::~CPlayerStatusComponent()
{
}

void CPlayerStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPlayerStatusComponent>(this);
}

void CPlayerStatusComponent::SetStatus(ECharacterType type)
{
	CGameDataManager* GDM = CGameDataManager::GetInst();

	/* 초기 스탯 저장 */
	{
		const FCharacterData& data = GDM->GetCharacterDataManager()->GetCharacterData(type);

		mBaseAttack      = data.baseAttack;
		mBaseDefense     = data.baseDefense;
		mBaseMaxHP       = data.baseMaxHP;
		mBaseAttackSpeed = data.baseAttackSpeed;
		mBaseMoveSpeed   = data.baseMoveSpeed;
		mBasePickupRange = data.basePickUpRange;
		mBaseGrowthExp   = data.baseGrowthExp;
	}

	/* 파워업 관련 */
	{
		/* 메뉴에서 구매한 파워업 저장 */
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mMenuPowerUps[i] = GDM->GetPlayerProfile()->GetMenuPowerUpLvl((EPowerUpType)i);

		/* 파워업 레벨업 당 증가비율 저장 */
		for (int i = 0; i < (int)EPowerUpType::MAX; i++)
			mPowerUpModifiers[i] = GDM->GetItemDataManager()->GetPowerUpData((EPowerUpType)i).statModifier;
	}

	// 초기 체력 설정
	mMaxHP = mBaseMaxHP + mMenuPowerUps[(int)EPowerUpType::MAX_HEALTH] * mPowerUpModifiers[(int)EPowerUpType::MAX_HEALTH];
	mHP	   = mMaxHP;
}

void CPlayerStatusComponent::AddHP(float hp)
{
	mHP = std::clamp(mHP + hp, 0.0f, mMaxHP);

	float percent = mHP / mMaxHP;
	CEventManager::GetInst()->Broadcast(EEventType::PLAYER_HP_CHANGED, &percent);

	if (mHP <= 0.0f)
		CEventManager::GetInst()->Broadcast(EEventType::GOTO_PLAY_SUB_STATE_GAMEOVER);
}

void CPlayerStatusComponent::AddExp(float exp)
{
	mExp += exp;

	while (mExp >= mExpToLevelUp)
	{
		mExp -= mExpToLevelUp;
		mLevel++;
		mExpToLevelUp = (float)(2 * mLevel * mLevel + 10);

		mPendingLevelUps++;
	}
	ProcessPendingLevelUp(0.0f);

	float percent = mExp / mExpToLevelUp;
	CEventManager::GetInst()->Broadcast(EEventType::PLAYER_EXP_GAINED, &percent);
}

void CPlayerStatusComponent::ProcessPendingLevelUp(float delayTime)
{
	if (mPendingLevelUps)
	{
		mPendingLevelUps--;

		CEventManager::GetInst()->Broadcast(EEventType::GOTO_PLAY_SUB_STATE_LVLUP, nullptr, delayTime);
		CEventManager::GetInst()->Broadcast(EEventType::PLAYER_LEVEL_UP_BEGIN, &mLevel, delayTime);
	}
}