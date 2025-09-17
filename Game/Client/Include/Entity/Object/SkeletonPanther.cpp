#include "SkeletonPanther.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonPanther::CSkeletonPanther()
{
}

CSkeletonPanther::~CSkeletonPanther()
{
}

bool CSkeletonPanther::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonPanther");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonPanther");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(34.0f, 33.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonPantherHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(40.0f, 27.5f);
	hitbox->GetTransform()->SetRelativePos(0.0f, 5.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonPantherFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(40.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 20.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeletonPanther::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonPanther>(this);
}