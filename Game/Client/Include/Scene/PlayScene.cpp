#include "PlayScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Scene/UI/PlayUI.h"
#include "../Scene/Camera.h"
#include "Collision/SceneCollision.h"
#include "../Entity/Object/AllObjects.h"
#include "../Core/Input.h"

CPlayScene::CPlayScene()
{
    mSceneUI = new CPlayUI;

    mCamera = new CCamera;
    mCamera->SetResolution(CGameManager::GetInst()->GetResolution());

    mSceneCollision = new CSceneCollision(mCamera);
}

CPlayScene::~CPlayScene()
{
    SAFE_DELETE(mSceneCollision);
    SAFE_DELETE(mCamera);
    SAFE_DELETE(mSceneUI);
}

bool CPlayScene::Enter()
{
    mSceneUI->Init();

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

void CPlayScene::Update(float deltaTime)
{
    CScene::Update(deltaTime);

    if (CInput::GetInst()->GetKeyState(SDL_SCANCODE_ESCAPE, EKey::State::PRESS))
        CSceneManager::GetInst()->ChangeRequest(ETransition::PUSH, ESceneState::PAUSE);
}

void CPlayScene::LoadResources()
{
    LoadTexture("Texture_UIAtlas", "UIAtlas.png");

    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    LoadTexture("Texture_Tralala", "Tralala.png");
    LoadTexture("Texture_Sahur", "Sahur.png");
    LoadTexture("Texture_Bananini", "Bananini.png");

    LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

    LoadBGM("BGM_MadForest", "bgm_italian_brainrot.wav");

    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}