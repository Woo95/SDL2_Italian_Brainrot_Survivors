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

	return CObject::Init();
}