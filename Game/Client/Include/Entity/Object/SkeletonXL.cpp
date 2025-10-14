#include "SkeletonXL.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonXL::CSkeletonXL()
{
}

CSkeletonXL::~CSkeletonXL()
{
}

bool CSkeletonXL::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_SkeletonXL");
	mStatus->SetStatus(ERegularMobType::SKELETON_XL);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonXL");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonXL");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(38.0f, 48.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonXLHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(30.0f, 57.5f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, 0.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonXLFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(28.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 30.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeletonXL::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonXL>(this);
}