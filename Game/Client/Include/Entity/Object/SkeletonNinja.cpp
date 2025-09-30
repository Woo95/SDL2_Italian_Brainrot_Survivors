#include "SkeletonNinja.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonNinja::CSkeletonNinja()
{
}

CSkeletonNinja::~CSkeletonNinja()
{
}

bool CSkeletonNinja::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_SkeletonNinja");
	mStatus->SetStatus(ERegularMobType::SKELETON_NINJA);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonNinja");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonNinja");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(34.0f, 34.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonNinjaHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(25.0f, 40.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonNinjaFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 20.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeletonNinja::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonNinja>(this);
}