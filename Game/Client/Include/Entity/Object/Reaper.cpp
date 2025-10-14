#include "Reaper.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CReaper::CReaper()
{
}

CReaper::~CReaper()
{
}

bool CReaper::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Reaper");
	mStatus->SetStatus(ESubBossMobType::REAPER);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Reaper");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Reaper");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_ReaperHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CReaper::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CReaper>(this);
}