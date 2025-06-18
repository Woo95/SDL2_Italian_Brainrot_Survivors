#include "Sahur.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CSahur::CSahur()
{
}

CSahur::~CSahur()
{
}

bool CSahur::Init()
{
	mMovement = AllocateComponent<CMovementComponent>("Movement_Sahur");
	mRootComponent->AddChild(mMovement);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	mSprite->SetTexture("Texture_Sahur");
	mSprite->SetAnimation("Sahur");
	mSprite->GetAnimation()->SetCurrentState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(57.f, 67.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SahurHitbox");
	hitbox->SetProfile("PlayerHitBox");
	hitbox->GetTransform()->SetWorldScale(25.f, 50.f);
	hitbox->GetTransform()->SetWorldPos(0.0f, -8.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SahurFoot");
	foot->SetProfile("PlayerFoot");
	foot->GetTransform()->SetWorldScale(20.f, 10.f);
	foot->GetTransform()->SetWorldPos(0.0f, 30.f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	mRigidbody = AllocateComponent<CRigidbody>("Rigidbody_Sahur");
	mRootComponent->AddChild(mRigidbody);

	return CPlayer::Init();
}

void CSahur::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSahur>(this);
}