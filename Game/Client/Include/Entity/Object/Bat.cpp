#include "Bat.h"
#include "Enemy.h"
#include "../Component/AllComponents.h"
#include "../../Resource/Animation.h"

CBat::CBat()
{
}

CBat::~CBat()
{
}

bool CBat::Init()
{	
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_BatVfx");
	mSprite->SetTexture("Texture_VfxAtlas");
	mSprite->SetAnimation("Bat");
	mSprite->GetAnimation()->SetState(EAnimationState::IDLE);
	mSprite->GetTransform()->SetWorldScale(35.0f, 35.0f);
	mSprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(mSprite);

	CCircleCollider* collider = AllocateComponent<CCircleCollider>("BoxCollider_Bat");
	collider->SetProfile("PlayerWeapon");
	collider->GetTransform()->SetWorldScale(35.0f, 35.0f);
	collider->GetTransform()->SetPivot(0.5f, 0.5f);
	collider->AddCallbackFunc<CBat>(ECollider::OnCollision::ENTER, this, &CBat::OnCollisionEnter);
	mRootComponent->AddChild(collider);

	mRigidbody = AllocateComponent<CRigidbody>("Rigidbody_Bat");
	mRigidbody->SetGravityScale(5.0f);
	mRootComponent->AddChild(mRigidbody);

	return CObject::Init();
}

void CBat::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	mDestroyTime -= deltaTime;
	if (mDestroyTime < 0.0f)
		Destroy();
}

void CBat::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBat>(this);
}

void CBat::SetFlip(SDL_RendererFlip flip)
{
	mSprite->SetFlip(flip);
}

void CBat::OnCollisionEnter(CCollider* self, CCollider* other)
{
	if (CEnemy* enemy = dynamic_cast<CEnemy*>(other->GetObject()))
	{
		enemy->TakeDamage(mDamage);
	}
}