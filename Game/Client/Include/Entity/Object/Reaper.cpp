#include "Reaper.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CReaper::CReaper()
{
}

CReaper::~CReaper()
{
}

bool CReaper::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Reaper");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Reaper");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_ReaperHitbox");
	hitbox->SetProfile("EnemyHitBox");
	hitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_ReaperFoot");
	foot->SetProfile("EnemyFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 10.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 30.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CEnemy::Init();
}

void CReaper::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CReaper>(this);
}