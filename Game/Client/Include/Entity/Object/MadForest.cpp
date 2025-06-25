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

#pragma region Gravestone
	evnObj = mScene->InstantiateObject<CScrollEnvObj, 40>("EvnObj_Gravestone1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(31.75f, 50.35f);
	evnObj->GetTransform()->SetWorldPos(355.0f, 127.5f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Gravestone1");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.3f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 0.345f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj, 40>("EvnObj_Gravestone2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(31.75f, 50.35f);
	evnObj->GetTransform()->SetWorldPos(410.0f, 127.5f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Gravestone1");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.3f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 0.345f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Gravestone3", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(29.2f, 51.0f);
	evnObj->GetTransform()->SetWorldPos(518.0f, 118.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Gravestone2");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.1f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.92f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.0f);
#pragma endregion

#pragma region Column
	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Column1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(44.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(247.0f, 279.8f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Column");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.85f, 0.28f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -0.45f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Column2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(44.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(633.73f, 279.8f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Column");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.85f, 0.28f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -0.45f);
#pragma endregion

#pragma region Tree
	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(856.75f, 115.24f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(525.06f, 337.8f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree3", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(745.0f, 281.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree4", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(964.5f, 224.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree5", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(416.0f, 612.5f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree6", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(802.84f, 557.26f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree7", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(2565.0f, 445.6f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree8", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3066.0f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree9", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3122.0f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree10", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3231.4f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree11", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3287.4f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree12", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3398.0f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1NoLeaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree13", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(52.0f, 110.0f);
	evnObj->GetTransform()->SetWorldPos(3454.0f, 887.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree1Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.6f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.37f, 0.14f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.8f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree14", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(2399.1f, 1659.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree15", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(2896.3f, 1659.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree16", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(2785.7f, 2653.3f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2Leaf");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Tree17", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(87.45f, 140.25f);
	evnObj->GetTransform()->SetWorldPos(3012.76f, 2653.3f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Tree2Leaf");
	evnObj->GetComponent<CSpriteComponent>()->SetFlip(SDL_FLIP_HORIZONTAL);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.7f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.12f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.5f);
#pragma endregion

#pragma region Totem
	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Totem1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(34.0f, 57.8f);
	evnObj->GetTransform()->SetWorldPos(2455.5f, 1700.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Totem4");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.2f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.6f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Totem2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(33.0f, 72.6f);
	evnObj->GetTransform()->SetWorldPos(2841.9f, 1698.6f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Totem1");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.2f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.4f, -1.6f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Totem3", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(32.3f, 57.8f);
	evnObj->GetTransform()->SetWorldPos(2886.5f, 1696.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Totem2");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.2f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.95f, -1.6f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Totem4", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(FVector2D(14.0f, 48.0f) * 1.7f);
	evnObj->GetTransform()->SetWorldPos(2916.16f, 1696.3f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Totem3");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.2f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.8f, -1.6f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Totem5", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(34.0f, 57.8f);
	evnObj->GetTransform()->SetWorldPos(2953.0f, 1865.0f);
	evnObj->GetComponent<CSpriteComponent>()->SetTexture("Texture_MadForestTexturePack");
	evnObj->GetComponent<CSpriteComponent>()->SetFrame("Totem4");
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	evnObj->GetComponent<CSpriteComponent>()->GetTransform()->SetPivot(0.5f, 0.45f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(0.25f, 0.2f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetPivot(0.5f, -1.6f);
#pragma endregion

#pragma region Bush
	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush1", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(55.0f, 310.0f);
	evnObj->GetTransform()->SetWorldPos(1325.0f, 2370.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush2", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(329.0f, 87.0f);
	evnObj->GetTransform()->SetWorldPos(1380.5f, 2370.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush3", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(60.0f, 280.0f);
	evnObj->GetTransform()->SetWorldPos(1710.1f, 2399.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush4", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(55.0f, 72.0f);
	evnObj->GetTransform()->SetWorldPos(1381.3f, 2608.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush5", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(55.0f, 30.0f);
	evnObj->GetTransform()->SetWorldPos(1437.0f, 2608.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush6", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(55.0f, 77.0f);
	evnObj->GetTransform()->SetWorldPos(1654.0f, 2602.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);

	evnObj = mScene->InstantiateObject<CScrollEnvObj>("EvnObj_Bush7", ELayer::OBJECT);
	evnObj->SetMapScale(mapScale);
	evnObj->GetTransform()->SetWorldScale(42.0f, 50.0f);
	evnObj->GetTransform()->SetWorldPos(1610.6f, 2602.0f);
	evnObj->GetComponent<CBoxCollider>()->GetTransform()->SetRelativeScale(1.0f, 1.0f);
#pragma endregion
}