#include "Drowner.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CDrowner::CDrowner()
{
}

CDrowner::~CDrowner()
{
}

bool CDrowner::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Drowner");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Drowner");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_DrownerHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_DrownerFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 10.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 30.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CDrowner::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CDrowner>(this);
}