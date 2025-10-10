#include "PlayScene.h"
#include "Extension/Camera.h"
#include "Extension/SceneCollision.h"
#include "Extension/PlayUI.h"
#include "Extension/MobSpawner.h"
#include "Extension/LevelUpHandler.h"
#include "../Engine.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"
#include "../Entity/Object/AllObjects.h"
#include "../Entity/Component/AllComponents.h"
#include "../Widget/AllWidgets.h"

CPlayScene::CPlayScene()
{
    mCamera = new CCamera;
    mCamera->SetResolution(CEngine::GetInst()->GetResolution());
	mSceneCollision = new CSceneCollision(mCamera);
	mSceneUI = new CPlayUI;

	mMobSpawner = new CMobSpawner(this);
	mLevelUpHandler = new CLevelUpHandler(this);
}

CPlayScene::~CPlayScene()
{
	SAFE_DELETE(mLevelUpHandler);
	SAFE_DELETE(mMobSpawner);

	SAFE_DELETE(mSceneUI);
	SAFE_DELETE(mSceneCollision);
	SAFE_DELETE(mCamera);
}

bool CPlayScene::Enter(void* payload)
{
	BindEventListeners();

	// UI //
	mSceneUI->Init();
	SetSubState(EPlaySubState::PLAY);

    // Sound //
    CSoundManager* SM = CAssetManager::GetInst()->GetSoundManager();
    SM->SetVolume<CBGM>(SM->GetVolume<CBGM>());
    SM->GetSound<CBGM>("BGM_MadForest")->Play();

    // Entity //
    InstantiateObject<CMadForest, 1>("Object_MadForest", ELayer::BACKGROUND);
    mPlayer = InstantiatePlayer();

    // Camera //
    mCamera->SetTarget(mPlayer);

	// Spawner //
	mMobSpawner->Init();

	// LevelUpHandler //
	mLevelUpHandler->Init();

    return true;
}

bool CPlayScene::Exit()
{
	CEventManager::GetInst()->ClearListener();

    return true;
}

void CPlayScene::Update(float deltaTime)
{
	/* UpdateState */
	switch (mSubState)
	{
	case EPlaySubState::PLAY:
		mTime += deltaTime;
		((CPlayUI*)mSceneUI)->GetPlayPanel()->SetGameTime(mTime);
		CScene::Update(deltaTime);
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
	LoadTexture("Texture_VfxAtlas", "VfxAtlas.png");
	LoadTexture("Texture_OverlayBG", "OverlayBG.png");
	LoadTexture("Texture_GameOver", "GameOver.png");

    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    std::string charName = CGameDataManager::GetInst()->GetPlayerProfile()->GetName();
    LoadTexture("Texture_" + charName, (charName + ".png").c_str());

	LoadTexture("Texture_Boss", "BossAtlas.png");
	LoadTexture("Texture_Mob", "MobAtlas.png");

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

CPlayer* CPlayScene::InstantiatePlayer()
{
	CPlayer* player = nullptr;
	CWeaponComponent* weapon = nullptr;
	switch (CGameDataManager::GetInst()->GetPlayerProfile()->GetType())
	{
	case ECharacterType::TRALALA:
		player = InstantiateObject<CTralala, 1>("Player_Tralala", ELayer::OBJECT);
		player->AddWeapon(EWeaponType::BUBBLE);
		((CPlayUI*)mSceneUI)->GetPlayPanel()->SetInventorySlot(EWeaponType::BUBBLE);
	    break;
	case ECharacterType::SAHUR:
	{
		player = InstantiateObject<CSahur, 1>("Player_Sahur", ELayer::OBJECT);
		player->AddWeapon(EWeaponType::BAT);
		((CPlayUI*)mSceneUI)->GetPlayPanel()->SetInventorySlot(EWeaponType::BAT);
		break;
	}
	case ECharacterType::BANANINI:
		player = InstantiateObject<CBananini, 1>("Player_Bananini", ELayer::OBJECT);
		player->AddWeapon(EWeaponType::BANANA);
		((CPlayUI*)mSceneUI)->GetPlayPanel()->SetInventorySlot(EWeaponType::BANANA);
	    break;
	}
	return player;
}

void CPlayScene::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 씬 전환 관련
	EM->AddListener(EEventType::GOTO_RESULT_SCENE, [this](void* data)
	{
		FResultData* resultData = new FResultData
		(
			mTime,
			mPlayer->GetStatus()->GetLevel(),
			mPlayer->GetStatus()->GetGoldEarned(),
			mPlayer->GetStatus()->GetKillCount()
		);
		CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::RESULT, resultData);
	});

	// 서브 씬 전환 관련
	EM->AddListener(EEventType::GOTO_PLAY_SUB_STATE_PLAY, [this](void*)
	{
		SetSubState(EPlaySubState::PLAY);
	});
	EM->AddListener(EEventType::GOTO_PLAY_SUB_STATE_PAUSE, [this](void*)
	{
		SetSubState(EPlaySubState::PAUSE);
	});
	EM->AddListener(EEventType::GOTO_PLAY_SUB_STATE_LVLUP, [this](void*)
	{
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_LevelUp")->Play();
		SetSubState(EPlaySubState::LVLUP);
	});
	EM->AddListener(EEventType::PLAYER_LEVEL_UP_SELECT, [this](void* item)
	{
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();
		SetSubState(EPlaySubState::PLAY);
	});
	EM->AddListener(EEventType::GOTO_PLAY_SUB_STATE_GAMEOVER, [this](void*)
	{
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CBGM>("BGM_MadForest")->Stop();
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_GameOver")->Play();
		SetSubState(EPlaySubState::GAMEOVER);
	});
}