#include "Gem.h"
#include "Player.h"
#include "../Component/AllComponents.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

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
	collider->AddCallbackFunc<CGem>(ECollider::OnCollision::ENTER, this, &CGem::OnCollisionEnter);
	mRootComponent->AddChild(collider);

	mChase = AllocateComponent<CChaseComponent>("Chase_Gem");
	mChase->SetSpeed(400.0f);
	mRootComponent->AddChild(mChase);

	return CObject::Init();
}

void CGem::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CGem>(this);
}

void CGem::OnCollisionEnter(CCollider* self, CCollider* other)
{
	if (CPlayer* player = dynamic_cast<CPlayer*>(other->GetObject()))
	{
		if (other == player->GetPickUpZone())
		{
			mChase->SetTarget(other->GetObject()->GetTransform());
		}
		else if (other == player->GetHitbox())
		{
			CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_Gem")->Play();
			player->AddExp(GetExp());
			Destroy();
		}
	}
}