#include "ChaseComponent.h"
#include "../Object/Object.h"

CChaseComponent::CChaseComponent() :
	mSpeed(100.f),
	mFacingDir(FVector2D::ZERO),
	mSelf(nullptr),
	mTarget(nullptr)
{
	mTypeID = typeid(CChaseComponent).hash_code();
}

CChaseComponent::~CChaseComponent()
{
}

bool CChaseComponent::Init()
{
	CComponent::Init();

	mSelf = mObject->GetTransform();

	return true;
}

void CChaseComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (!mTarget || !mSelf)
		return;

	FVector2D delta = mTarget->GetWorldPos() - mSelf->GetWorldPos();
	if (delta != FVector2D::ZERO)
	{
		mFacingDir = delta.GetNormalize();
		mSelf->SetWorldPos(mSelf->GetWorldPos() + mFacingDir * mSpeed * deltaTime);
	}
}

void CChaseComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CChaseComponent>(this);
}