#include "ScrollEnvObj.h"
#include "../Component/AllComponents.h"
#include "../../Manager/SceneManager.h"
#include "../../Scene/PlayScene.h"
#include "../../Scene/Camera.h"

CScrollEnvObj::CScrollEnvObj() :
    mCamera(nullptr),
    mMapScale(0.0f, 0.0f),
    mSnapThreshold(0.0f),
    mSprite(nullptr),
    mCollider(nullptr)
{
}

CScrollEnvObj::~CScrollEnvObj()
{
}

bool CScrollEnvObj::Init()
{
    mCamera = CSceneManager::GetInst()->GetCurrentScene()->GetCamera();

    mSprite = AllocateComponent<CSpriteComponent, 50>("Sprite_EvnObj");

    mCollider = AllocateComponent<CBoxCollider, 50>("BoxCollider_EvnObj");
    mCollider->SetProfile("Environment");

    mRootComponent->AddChild(mSprite);
    mRootComponent->AddChild(mCollider);

    return CObject::Init();
}

void CScrollEnvObj::Update(float deltaTime)
{
    CObject::Update(deltaTime);

    FVector2D cameraPos = mCamera->GetLookAt();
    FVector2D objPos = GetTransform()->GetWorldPos();
    FVector2D delta = cameraPos - objPos;

    // 카메라 기준으로 오브젝트가 얼마나 떨어졌는지 거리 계산
    float snapDistance = delta.Length();

    // 일정 거리 이상 떨어졌을 때만 위치 보정
    if (snapDistance >= mSnapThreshold)
    {
        // 오브젝트 기준으로 카메라와의 상대 방향을 계산 (-1, 0, 1)
        int directionX = (int)roundf(delta.x / mMapScale.x);
        int directionY = (int)roundf(delta.y / mMapScale.y);

        // 방향에 따라 이동해야 할 보정 거리 계산
        float offsetX = mMapScale.x * directionX;
        float offsetY = mMapScale.y * directionY;

        GetTransform()->SetWorldPos(objPos + FVector2D(offsetX, offsetY));
    }
}

void CScrollEnvObj::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CScrollEnvObj>(this);
}