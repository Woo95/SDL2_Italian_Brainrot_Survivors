#include "StatusComponent.h"

CStatusComponent::CStatusComponent()
{
	mTypeID = typeid(CStatusComponent).hash_code();
}

CStatusComponent::~CStatusComponent()
{

}

bool CStatusComponent::Init()
{
	return CComponent::Init();
}

void CStatusComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CStatusComponent>(this);
}