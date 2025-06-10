#include "EnvObj.h"
#include "../Component/AllComponents.h"

CEvnObj::CEvnObj() :
	mSprite(nullptr),
	mCollider(nullptr)
{
}

CEvnObj::~CEvnObj()
{
}

bool CEvnObj::Init()
{
	mSprite = AllocateComponent<CSpriteComponent>("Sprite_EvnObj");

	mCollider = AllocateComponent<CBoxCollider>("BoxCollider_EvnObj");
	mCollider->SetProfile("Environment");

	mRootComponent->AddChild(mSprite);
	mRootComponent->AddChild(mCollider);

	return CObject::Init();
}

void CEvnObj::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	//mRootComponent->GetTransform()->SetWorldPos();
}

void CEvnObj::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CEvnObj>(this);
}

void CEvnObj::SetColliderWorldScale(float x, float y)
{
	mCollider->GetTransform()->SetWorldScale(x, y);
}

void CEvnObj::SetSpriteTexture(const std::string& key)
{
	mSprite->SetTexture(key);
}

void CEvnObj::SetSpriteWorldScale(float x, float y)
{
	mSprite->GetTransform()->SetWorldScale(x, y);
}