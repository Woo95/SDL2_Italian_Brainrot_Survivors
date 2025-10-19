#include "Trickster.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CTrickster::CTrickster()
{
	mGemType = CEnemy::RED;
	mGemSpawnRate = 1.0f;
}

CTrickster::~CTrickster()
{
}

bool CTrickster::Init()
{
	mStatus = AllocateComponent<CEnemyStatusComponent, 50>("Status_Trickster");
	mStatus->SetStatus(ESubBossMobType::TRICKSTER);
	mRootComponent->AddChild(mStatus);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Trickster");
	mSprite->SetTexture("Texture_Boss");
	mSprite->SetAnimation("Trickster");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(41.0f, 47.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_TricksterHitbox");
	mHitbox->SetProfile("EnemyHitbox");
	mHitbox->GetTransform()->SetRelativeScale(32.0f, 52.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -3.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

	return CEnemy::Init();
}

void CTrickster::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTrickster>(this);
}