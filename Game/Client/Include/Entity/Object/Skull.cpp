#include "Skull.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSkull::CSkull()
{
}

CSkull::~CSkull()
{
}

bool CSkull::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Skull");
	mSprite->SetTexture("Texture_Mob");
	mSprite->SetAnimation("Skull");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(28.0f, 33.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CCircleCollider>("CircleCollider_SkullHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(30.0f, 30.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -2.5f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	return CEnemy::Init();
}

void CSkull::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSkull>(this);
}