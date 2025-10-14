#include "SkeletonKnife.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonKnife::CSkeletonKnife()
{
}

CSkeletonKnife::~CSkeletonKnife()
{
}

bool CSkeletonKnife::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_SkeletonKnife");
	mStatus->SetStatus(ERegularMobType::SKELETON_KNIFE);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonKnife");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonKnife");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(28.0f, 32.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonKnifeHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(25.0f, 40.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonKnifeFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 20.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeletonKnife::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonKnife>(this);
}