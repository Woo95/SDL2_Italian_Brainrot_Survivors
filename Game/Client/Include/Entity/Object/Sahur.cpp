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
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	mSprite->SetTexture("Texture_Sahur");
	mSprite->SetAnimation("Sahur");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(38.0f, 45.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_SahurHitbox");
	hitbox->SetProfile("PlayerHitBox");
	hitbox->GetTransform()->SetRelativeScale(25.0f, 50.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -8.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_SahurFoot");
	foot->SetProfile("PlayerFoot");
	foot->GetTransform()->SetRelativeScale(23.0f, 10.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 30.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CPlayer::Init();
}

void CSahur::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSahur>(this);
}

void CSahur::OnMoveDirChanged(const FVector2D& dir)
{
	if (mMovement->GetMoveDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	if (mMovement->GetMoveDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}