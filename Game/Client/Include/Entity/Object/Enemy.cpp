#include "Enemy.h"
#include "../Component/AllComponents.h"

CEnemy::CEnemy() :
	mChase(nullptr),
	mSprite(nullptr)
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
	mChase = AllocateComponent<CChaseComponent, 50>("Chase_Enemy");
	mRootComponent->AddChild(mChase);

	mRigidbody = AllocateComponent<CRigidbody>("Rigidbody_Enemy");
	mRootComponent->AddChild(mRigidbody);

	return CObject::Init();
}

void CEnemy::Update(float deltaTime)
{
	CObject::Update(deltaTime);

	if (mChase->GetFacingDir().x < 0)
	{
		mSprite->SetFlip(SDL_FLIP_NONE);
	}
	else if (mChase->GetFacingDir().x > 0)
	{
		mSprite->SetFlip(SDL_FLIP_HORIZONTAL);
	}
}