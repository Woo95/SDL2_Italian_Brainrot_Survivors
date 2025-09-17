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
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonXL");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonXL");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(38.0f, 48.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonXLHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(30.0f, 57.5f);
	hitbox->GetTransform()->SetRelativePos(0.0f, 0.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

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