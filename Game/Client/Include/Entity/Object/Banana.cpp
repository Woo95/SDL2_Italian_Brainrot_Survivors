#include "Banana.h"
#include "../Component/AllComponents.h"

CBanana::CBanana()
{
}

CBanana::~CBanana()
{
}

bool CBanana::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_BananaVfx");
	mSprite->SetTexture("Texture_VfxAtlas");
	mSprite->SetFrame("Banana");
	mSprite->GetTransform()->SetWorldScale(mScale);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	mCollider = AllocateComponent<CCircleCollider>("CircleCollider_Banana");
	mCollider->SetProfile("PlayerWeapon");
	mCollider->GetTransform()->SetWorldScale(mScale);
	mCollider->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mCollider);

	return CObject::Init();
}

void CBanana::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBanana>(this);
}

void CBanana::SetScale(const FVector2D& scale)
{
	mScale = scale;

	mSprite->GetTransform()->SetWorldScale(mScale);
	mCollider->GetTransform()->SetWorldScale(mScale);
}