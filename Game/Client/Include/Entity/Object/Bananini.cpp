#include "Bananini.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CBananini::CBananini()
{
}

CBananini::~CBananini()
{
}

bool CBananini::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Bananini");
	mSprite->SetTexture("Texture_Bananini");
	mSprite->SetAnimation("Bananini");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(59.0f, 50.0f) * 1.2f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_BananiniHitbox");
	hitbox->SetProfile("PlayerHitBox");
	hitbox->GetTransform()->SetRelativeScale(25.f, 55.f);
	hitbox->GetTransform()->SetRelativePos(0.0f, 0.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	CCollider* foot = AllocateComponent<CBoxCollider>("BoxCollider_BananiniFoot");
	foot->SetProfile("PlayerFoot");
	foot->GetTransform()->SetRelativeScale(30.0f, 5.0f);
	foot->GetTransform()->SetRelativePos(0.0f, 30.0f);
	foot->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(foot);

	return CPlayer::Init();
}

void CBananini::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBananini>(this);
}

void CBananini::OnMoveDirChanged(const FVector2D& dir)
{
	if (dir == FVector2D::LEFT)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	else if (dir == FVector2D::RIGHT)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}