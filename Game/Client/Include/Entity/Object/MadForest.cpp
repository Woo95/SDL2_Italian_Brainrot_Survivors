#include "MadForest.h"
#include "../Component/ScrollMapComponent.h"
#include "../../Scene/Scene.h"
#include "../Object/EnvObj.h"

CMadForest::CMadForest()
{
}

CMadForest::~CMadForest()
{
}

bool CMadForest::Init()
{
	SetEnvObjects();

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

void CMadForest::SetEnvObjects()
{
	CEvnObj* evnObj;

	evnObj = mScene->InstantiateObject<CEvnObj, 40>("Object_EvnObj_E1", ELayer::OBJECT);
	evnObj->SetColliderWorldScale(35.5f, 53.f);
	evnObj->GetTransform()->SetWorldPos(339.f, 110.f);

	evnObj = mScene->InstantiateObject<CEvnObj>("Object_EvnObj_E2", ELayer::OBJECT);
	evnObj->SetColliderWorldScale(35.5f, 53.f);
	evnObj->GetTransform()->SetWorldPos(393.5f, 110.f);;

	evnObj = mScene->InstantiateObject<CEvnObj>("Object_EvnObj_E3", ELayer::OBJECT);
	evnObj->SetColliderWorldScale(31.f, 52.5f);
	evnObj->GetTransform()->SetWorldPos(506.57f, 113.3f);
}