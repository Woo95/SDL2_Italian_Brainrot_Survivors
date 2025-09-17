#include "Trickster.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CTrickster::CTrickster()
{
}

CTrickster::~CTrickster()
{
}

bool CTrickster::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Trickster");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Trickster");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_TricksterHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	return CEnemy::Init();
}

void CTrickster::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTrickster>(this);
}