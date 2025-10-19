#include "Drowner.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CDrowner::CDrowner()
{
	mGemType = CEnemy::RED;
	mGemSpawnRate = 1.0f;
}

CDrowner::~CDrowner()
{
}

bool CDrowner::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Drowner");
	mStatus->SetStatus(ESubBossMobType::DROWNER);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Drowner");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Drowner");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_DrownerHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CDrowner::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CDrowner>(this);
}