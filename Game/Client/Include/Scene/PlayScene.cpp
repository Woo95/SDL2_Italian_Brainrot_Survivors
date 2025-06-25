#include "PlayScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
#include "../Scene/Camera.h"
#include "Collision/SceneCollision.h"
#include "../Entity/Object/AllObjects.h"

CPlayScene::CPlayScene()
{
    mCamera = new CCamera;
    mCamera->SetResolution(CGameManager::GetInst()->GetResolution());

    mSceneCollision = new CSceneCollision(mCamera);
}

CPlayScene::~CPlayScene()
{
    SAFE_DELETE(mSceneCollision);
    SAFE_DELETE(mCamera);
}

bool CPlayScene::Enter()
{
    // Sound //
    CSoundManager* SM = CAssetManager::GetInst()->GetSoundManager();
    SM->SetVolume<CBGM>(SM->GetVolume<CBGM>());
    SM->GetSound<CBGM>("BGM_MadForest")->Play();

    // Entity //
    InstantiateObject<CMadForest, 1>("Object_MadForest", ELayer::BACKGROUND);

    CObject* player = InstantiateObject<CSahur, 1>("Player_Sahur", ELayer::OBJECT);

    mCamera->SetTarget(player);

    return true;
}

bool CPlayScene::Exit()
{
    return true;
}

void CPlayScene::LoadResources()
{
    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    LoadTexture("Texture_Tralala", "Tralala.png");
    LoadTexture("Texture_Sahur", "Sahur.png");
    LoadTexture("Texture_Bananini", "Bananini.png");

    LoadBGM("BGM_MadForest", "bgm_italian_brainrot.wav");

    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}