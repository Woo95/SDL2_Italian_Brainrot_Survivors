#include "Ender.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CEnder::CEnder()
{
}

CEnder::~CEnder()
{
}

bool CEnder::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Ender");
	mStatus->SetStatus(ESubBossMobType::ENDER);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Ender");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Ender");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_EnderHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(32.0f, 48.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_EnderFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(32.0f, 10.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 28.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CEnder::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CEnder>(this);
}