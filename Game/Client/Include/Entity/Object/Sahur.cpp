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
	mStatus = AllocateComponent<CPlayerStatusComponent, 1>("Status_Sahur");
	mStatus->SetStatus(ECharacterType::SAHUR);
	mRootComponent->AddChild(mStatus);

	mInventory = AllocateComponent<CInventoryComponent, 1>("Inventory_Sahur");
	mRootComponent->AddChild(mInventory);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Sahur");
	mSprite->SetTexture("Texture_Sahur");
	mSprite->SetAnimation("Sahur");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(38.0f, 45.0f) * 1.5f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	mRootComponent->AddChild(mSprite);

	mHitbox = AllocateComponent<CBoxCollider>("BoxCollider_SahurHitbox");
	mHitbox->SetProfile("PlayerHitbox");
	mHitbox->GetTransform()->SetRelativeScale(25.0f, 50.0f);
	mHitbox->GetTransform()->SetRelativePos(0.0f, -8.0f);
	mHitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mHitbox);

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
	if (mMovement->GetCurrMoveDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	if (mMovement->GetCurrMoveDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}