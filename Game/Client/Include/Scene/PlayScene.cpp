#include "PlayScene.h"
#include "UI/PlayUI.h"
#include "Camera.h"
#include "Collision/SceneCollision.h"
#include "PlayTimer.h"
#include "../Core/Input.h"
#include "../Manager/GameManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerState.h"
#include "../Entity/Object/AllObjects.h"

CPlayScene::CPlayScene() :
	mPlayTimer(nullptr)
{
    mSceneUI = new CPlayUI;

    mCamera = new CCamera;
    mCamera->SetResolution(CGameManager::GetInst()->GetResolution());

    mSceneCollision = new CSceneCollision(mCamera);

    mPlayTimer = new CPlayTimer;
}

CPlayScene::~CPlayScene()
{
    SAFE_DELETE(mSceneCollision);
    SAFE_DELETE(mCamera);
    SAFE_DELETE(mSceneUI);
    SAFE_DELETE(mPlayTimer);
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
    CObject* player = InstantiatePlayer();

    // Camera //
    mCamera->SetTarget(player);

    // Timer //
    mPlayTimer->SetTime(300.5f);

    return true;
}

bool CPlayScene::Exit()
{
    return true;
}

void CPlayScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	mPlayTimer->Update(deltaTime);
	static_cast<CPlayUI*>(mSceneUI)->SetGameTime(mPlayTimer->GetTime());

	if (CInput::GetInst()->GetKeyState(SDL_SCANCODE_ESCAPE, EKey::State::PRESS))
		CSceneManager::GetInst()->ChangeRequest(ETransition::PUSH, ESceneState::PAUSE);
}

void CPlayScene::LoadResources()
{
    LoadTexture("Texture_UIAtlas", "UIAtlas.png");

    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    std::string charName = CGameDataManager::GetInst()->GetPlayerState()->GetSelectedCharacterName();
    LoadTexture("Texture_" + charName, (charName + ".png").c_str());

    LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

    LoadBGM("BGM_MadForest", "bgm_italian_brainrot.wav");

    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}

CObject* CPlayScene::InstantiatePlayer()
{
    CObject* player = nullptr;

    switch (CGameDataManager::GetInst()->GetPlayerState()->GetSelectedCharacter())
    {
    case ECharacterType::TRALALA:
        player = InstantiateObject<CTralala, 1>("Player_Tralala", ELayer::OBJECT);
        break;
    case ECharacterType::SAHUR:
        player = InstantiateObject<CSahur, 1>("Player_Sahur", ELayer::OBJECT);
        break;
    case ECharacterType::BANANINI:
        player = InstantiateObject<CBananini, 1>("Player_Bananini", ELayer::OBJECT);
        break;
    }
    return player;
}