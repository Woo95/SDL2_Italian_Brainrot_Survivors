#include "MadForest.h"
#include "ScrollEnvObj.h"
#include "../Component/ScrollMapComponent.h"
#include "../Component/AllComponents.h"
#include "../../Scene/Scene.h"

CMadForest::CMadForest()
{
}

CMadForest::~CMadForest()
{
}

bool CMadForest::Init()
{
	mRootComponent->GetTransform()->SetWorldScale(3533.33f, 3533.33f);

	SetEnvObjects();

	CScrollMapComponent* scrollMap = AllocateComponent<CScrollMapComponent, 1>("ScrollMapComponent_MadForest");
	scrollMap->SetTexture("Texture_MadForest");
	scrollMap->SetFrame("MadForest");
	scrollMap->GetTransform()->SetWorldPos(0.0f, 0.0f);
	scrollMap->GetTransform()->SetWorldScale(mRootComponent->GetTransform()->GetWorldScale());

	mRootComponent->AddChild(scrollMap);

	return CObject::Init();
}

void CMadForest::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMadForest>(this);
}

void CMadForest::SetEnvObjects()
{
	const FVector2D& mapScale = mRootComponent->GetTransform()->GetWorldScale();

	CScrollEnvObj* evnObj;

	evnObj = mScene->InstantiateObject<CScrollEnvObj, 40>("Object_EvnObj_E1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	//evnObj->GetComponent<CSpriteComponent>()->SetTexture("");
	//evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetWorldScale(x, y);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetWorldScale(34.f, 53.f);
	evnObj->GetTransform()->SetWorldPos(339.f, 110.f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("Object_EvnObj_E2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	//evnObj->GetComponent<CSpriteComponent>()->SetTexture("");
	//evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetWorldScale(x, y);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetWorldScale(34.f, 53.f);
	evnObj->GetTransform()->SetWorldPos(394.f, 110.f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("Object_EvnObj_E3", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	//evnObj->GetComponent<CSpriteComponent>()->SetTexture("");
	//evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetWorldScale(x, y);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetWorldScale(31.f, 52.5f);
	evnObj->GetTransform()->SetWorldPos(506.57f, 113.3f);
}