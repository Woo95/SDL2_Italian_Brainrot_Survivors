#include "PlayScene.h"
#include "Extension/Camera.h"
#include "Extension/SceneCollision.h"
#include "Extension/PlayUI.h"
#include "Extension/MobSpawner.h"
#include "../Engine.h"
#include "../Manager/InputManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerState.h"
#include "../Entity/Object/AllObjects.h"

CPlayScene::CPlayScene()
{
    mCamera = new CCamera;
    mCamera->SetResolution(CEngine::GetInst()->GetResolution());
	mSceneCollision = new CSceneCollision(mCamera);
	mSceneUI = new CPlayUI;

	mMobSpawner = new CMobSpawner(mCamera);
}

CPlayScene::~CPlayScene()
{
	SAFE_DELETE(mMobSpawner);

	SAFE_DELETE(mSceneUI);
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
    CObject* player = InstantiatePlayer();

    // Camera //
    mCamera->SetTarget(player);

	// UI //
	mSceneUI->Init();
	SetSubState(EPlaySubState::PLAY);

	// Spawner //
	mMobSpawner->Init();
	mMobSpawner->SetPlayer(player);

    return true;
}

bool CPlayScene::Exit()
{
    return true;
}

void CPlayScene::Update(float deltaTime)
{
	/* UpdateState */
	switch (mSubState)
	{
	case EPlaySubState::PLAY:
		CScene::Update(deltaTime);

		mTime += deltaTime;
		((CPlayUI*)mSceneUI)->SetGameTime(mTime);

		mMobSpawner->Update(deltaTime);
		break;
	case EPlaySubState::PAUSE:
	case EPlaySubState::LVLUP:
	case EPlaySubState::GAMEOVER:
		mSceneUI->Update(deltaTime);
		break;
	}

	/* UpdateInput */
	if (CInputManager::GetInst()->GetKeyState(SDL_SCANCODE_ESCAPE, EKeyAction::PRESS))
	{
		switch (mSubState)
		{
		case EPlaySubState::PLAY:
			SetSubState(EPlaySubState::PAUSE);
			break;
		case EPlaySubState::PAUSE:
			SetSubState(EPlaySubState::PLAY);
			break;
		}
	}
}

void CPlayScene::LoadResources()
{
    LoadTexture("Texture_UIAtlas", "UIAtlas.png");
	LoadTexture("Texture_ItemAtlas", "ItemAtlas.png");
	LoadTexture("Texture_OverlayBG", "OverlayBG.png");
	LoadTexture("Texture_GameOver", "GameOver.png");

    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    std::string charName = CGameDataManager::GetInst()->GetPlayerState()->GetName();
    LoadTexture("Texture_" + charName, (charName + ".png").c_str());

    LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

    LoadBGM("BGM_MadForest", "bgm_italian_brainrot.wav");

    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
	LoadSFX("SFX_LevelUp", "sfx_levelup.wav");
	LoadSFX("SFX_GameOver", "sfx_gameOver.wav");
}

void CPlayScene::SetSubState(EPlaySubState state)
{
	mSubState = state;
    ((CPlayUI*)mSceneUI)->SetUIPanel(state);
}

CObject* CPlayScene::InstantiatePlayer()
{
    CObject* player = nullptr;

    switch (CGameDataManager::GetInst()->GetPlayerState()->GetType())
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