#include "SkeletonAngel.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonAngel::CSkeletonAngel()
{
}

CSkeletonAngel::~CSkeletonAngel()
{
}

bool CSkeletonAngel::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_SkeletonAngel");
	mStatus->SetStatus(ERegularMobType::SKELETON_ANGEL);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonAngel");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonAngel");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(34.0f, 34.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SkeletonAngelHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(25.0f, 40.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	return CEnemy::Init();
}

void CSkeletonAngel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonAngel>(this);
}