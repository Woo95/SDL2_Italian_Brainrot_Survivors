#include "Skeleton.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeleton::CSkeleton()
{
}

CSkeleton::~CSkeleton()
{
}

bool CSkeleton::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Skeleton");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("Skeleton");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(28.0f, 32.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(25.0f, 40.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 20.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeleton::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeleton>(this);
}