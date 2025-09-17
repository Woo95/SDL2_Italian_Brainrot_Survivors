#include "SkeletonMad.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonMad::CSkeletonMad()
{
}

CSkeletonMad::~CSkeletonMad()
{
}

bool CSkeletonMad::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonMad");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonMad");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(28.0f, 32.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonMadHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(23.0f, 40.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonMadFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 20.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CSkeletonMad::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonMad>(this);
}