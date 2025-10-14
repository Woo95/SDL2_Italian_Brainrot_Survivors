#include "Gem.h"
#include "../Component/AllComponents.h"

CGem::CGem()
{
}

CGem::~CGem()
{
}

bool CGem::Init()
{
	CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("Sprite_Gem");
	sprite->SetTexture("Texture_ItemAtlas");
	sprite->SetFrame("Gem");
	sprite->GetTransform()->SetWorldScale(FVector2D(9.0f, 12.0f) * 1.5f);
	sprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(sprite);

	CBoxCollider* collider = AllocateComponent<CBoxCollider>("BoxCollider_Gem");
	collider->SetProfile("PickableItem");
	collider->GetTransform()->SetWorldScale(sprite->GetTransform()->GetWorldScale());
	collider->GetTransform()->SetPivot(0.5f, 0.5f);
	collider->AddCallbackFunc<CGem>(ECollider::OnCollision::ENTER, this, &CGem::OnHit);
	mRootComponent->AddChild(collider);

	mChase = AllocateComponent<CChaseComponent>("Chase_Gem");
	mChase->SetSpeed(300.0f);
	mRootComponent->AddChild(mChase);

	return CObject::Init();
}

void CGem::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CGem>(this);
}

void CGem::OnHit(CCollider* self, CCollider* other)
{
	mChase->SetTarget(other->GetObject()->GetTransform());
}