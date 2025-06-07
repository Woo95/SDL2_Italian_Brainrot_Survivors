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
	CCollider* collider = AllocateComponent<CBoxCollider>("BoxCollider_Sahur");
	collider->SetProfile("Player");
	collider->GetTransform()->SetWorldScale(50.f, 75.f);
	collider->GetTransform()->SetPivot(0.5f, 0.5f);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	mSprite->SetTexture("Texture_Sahur");
	mSprite->SetAnimation("Sahur");
	mSprite->GetAnimation()->SetCurrentState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(50.f, 71.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);

	mRootComponent->AddChild(collider);
	mRootComponent->AddChild(mSprite);

	return CPlayer::Init();
}

void CSahur::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSahur>(this);
}