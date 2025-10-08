#include "Tralala.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CTralala::CTralala() :
	mFootCollider(nullptr)
{
}

CTralala::~CTralala()
{
}

bool CTralala::Init()
{
	mStatus = AllocateComponent<CPlayerStatusComponent, 1>("Status_Tralala");
	mStatus->SetStatus(ECharacterType::TRALALA);
	mRootComponent->AddChild(mStatus);

	mInventory = AllocateComponent<CInventoryComponent, 1>("Inventory_Tralala");
	mRootComponent->AddChild(mInventory);

	mSprite = AllocateComponent<CSpriteComponent>("Sprite_Tralala");
	mSprite->SetTexture("Texture_Tralala");
	mSprite->SetAnimation("Tralala");
	mSprite->GetAnimation()->SetState(EAnimationState::WALK);
	mSprite->GetTransform()->SetWorldScale(FVector2D(62.0f, 45.0f) * 1.3f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	mRootComponent->AddChild(mSprite);

	CCollider* hitbox = AllocateComponent<CBoxCollider>("BoxCollider_TralalaHitbox");
	hitbox->SetProfile("PlayerHitBox");
	hitbox->GetTransform()->SetRelativeScale(62.5f, 23.0f);
	hitbox->GetTransform()->SetRelativePos(0.0f, -7.0f);
	hitbox->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(hitbox);

	mFootCollider = AllocateComponent<CBoxCollider>("BoxCollider_TralalaFoot");
	mFootCollider->SetProfile("PlayerFoot");
	mFootCollider->GetTransform()->SetRelativeScale(42.0f, 13.0f);
	mFootCollider->GetTransform()->SetRelativePos(10.0f, 22.5f);
	mFootCollider->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mFootCollider);

	AddWeapon(EWeaponType::BUBBLE);

	return CPlayer::Init();
}

void CTralala::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTralala>(this);
}

void CTralala::OnMoveDirChanged(const FVector2D& dir)
{
	if (mMovement->GetMoveDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
		mFootCollider->GetTransform()->SetRelativePos(-10.0f, 22.5f);
	}
	if (mMovement->GetMoveDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
		mFootCollider->GetTransform()->SetRelativePos(10.0f, 22.5f);
	}
}