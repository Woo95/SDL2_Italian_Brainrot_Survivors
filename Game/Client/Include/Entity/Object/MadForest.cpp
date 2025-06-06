#include "MadForest.h"
#include "../Component/ScrollMapComponent.h"

CMadForest::CMadForest()
{
}

CMadForest::~CMadForest()
{
}

bool CMadForest::Init()
{
	CScrollMapComponent* scrollMap = AllocateComponent<CScrollMapComponent, 1>("ScrollMapComponent_MadForest");
	scrollMap->SetTexture("Texture_MadForest");
	scrollMap->SetFrame("MadForest");
	scrollMap->GetTransform()->SetWorldPos(0.0f, 0.0f);
	scrollMap->GetTransform()->SetWorldScale(3533.33f, 3533.33f);

	mRootComponent->AddChild(scrollMap);

	return CObject::Init();
}

void CMadForest::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMadForest>(this);
}