#include "Bubble.h"
#include "../Component/AllComponents.h"

CBubble::CBubble()
{
}

CBubble::~CBubble()
{
}

bool CBubble::Init()
{
	mMovement = AllocateComponent<CMovementComponent>("Movement");
	mMovement->SetSpeed(500.0f);
	mRootComponent->AddChild(mMovement);

	CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("Sprite_BubbleVfx");
	sprite->SetTexture("Texture_VfxAtlas");
	sprite->SetFrame("Bubble");
	sprite->GetTransform()->SetWorldScale(20.0f, 20.0f);
	sprite->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(sprite);

	CCollider* collider = AllocateComponent<CCircleCollider>("CircleCollider_Bubble");
	collider->SetProfile("PlayerWeapon");
	collider->GetTransform()->SetWorldScale(20.0f, 20.0f);
	collider->GetTransform()->SetPivot(0.5f, 0.5f);
	mRootComponent->AddChild(collider);

	return CObject::Init();
}

void CBubble::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	mMovement->AddMoveDir(mMoveDir);

	mDestroyTime -= deltaTime;
	if (mDestroyTime < 0.0f)
		Destroy();
}

void CBubble::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBubble>(this);
}