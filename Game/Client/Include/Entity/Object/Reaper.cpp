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
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Reaper");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	return CEnemy::Init();
}

void CReaper::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CReaper>(this);
}