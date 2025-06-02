#include "PlayScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
#include "../Scene/Camera.h"
#include "Collision/SceneCollision.h"
#include "../Entity/Object/Player.h"

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
    CObject* player = InstantiateObject<CPlayer, 1>("Object_Player", ELayer::OBJECT);

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

    LoadBGM("BGM_MadForest", "bgm_italian_brainrot.wav");

    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}