#include "Stalker.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CStalker::CStalker()
{
}

CStalker::~CStalker()
{
}

bool CStalker::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Stalker");
	mStatus->SetStatus(ESubBossMobType::STALKER);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Stalker");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Stalker");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_StalkerHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CStalker::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CStalker>(this);
}