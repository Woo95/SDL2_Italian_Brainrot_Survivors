#include "SkeletonDragon.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkeletonDragon::CSkeletonDragon()
{
	mGemType = CEnemy::BLUE;
	mGemSpawnRate = 0.5f;
}

CSkeletonDragon::~CSkeletonDragon()
{
}

bool CSkeletonDragon::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_SkeletonDragon");
	mStatus->SetStatus(ERegularMobType::SKELETON_DRAGON);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_SkeletonDragon");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("SkeletonDragon");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(48.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CCircleCollider>("CircleCollider_SkeletonDragonHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(55.0f, 55.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, 0.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CSkeletonDragon::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkeletonDragon>(this);
}