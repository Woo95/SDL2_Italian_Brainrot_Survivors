#include "SkeletonDragon.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonDragon::CSkeletonDragon()
{
}

CSkeletonDragon::~CSkeletonDragon()
{
}

bool CSkeletonDragon::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonDragon");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonDragon");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(48.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CCircleCollider>("CircleCollider_SkeletonDragonHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(55.0f, 55.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, 0.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	return CEnemy::Init();
}

void CSkeletonDragon::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonDragon>(this);
}