#include "EnemyStatusComponent.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/MobDataManager.h"

CEnemyStatusComponent::CEnemyStatusComponent()
{
	mTypeID = typeid(CEnemyStatusComponent).hash_code();
}

CEnemyStatusComponent::~CEnemyStatusComponent()
{
}

void CEnemyStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CEnemyStatusComponent>(this);
}

void CEnemyStatusComponent::SetStatus(ERegularMobType type)
{
	const FRegularMobData& mobData = CGameDataManager::GetInst()->GetMobDataManager()->GetMobData(type);

	mHP			= mobData.baseHP;
	mAttack		= mobData.baseAttack;
	mMoveSpeed	= mobData.baseMoveSpeed;
	mExp		= mobData.baseExp;
	mGold		= mobData.baseGold;
}

void CEnemyStatusComponent::SetStatus(ESubBossMobType type)
{
	const FSubBossMobData& mobData = CGameDataManager::GetInst()->GetMobDataManager()->GetMobData(type);

	mHP			= mobData.baseHP;
	mAttack		= mobData.baseAttack;
	mMoveSpeed	= mobData.baseMoveSpeed;
	mExp		= mobData.baseExp;
	mGold		= mobData.baseGold;
}