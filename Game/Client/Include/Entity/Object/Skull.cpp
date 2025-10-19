#include "Skull.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkull::CSkull()
{
	mGemType = CEnemy::BLUE;
	mGemSpawnRate = 0.5f;
}

CSkull::~CSkull()
{
}

bool CSkull::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Skull");
	mStatus->SetStatus(ERegularMobType::SKULL);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Skull");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("Skull");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(28.0f, 33.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CCircleCollider>("CircleCollider_SkullHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(30.0f, 30.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -2.5f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CSkull::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkull>(this);
}