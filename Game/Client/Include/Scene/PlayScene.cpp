#include "PlayScene.h"
#include "Extension/Camera.h"
#include "Extension/SceneCollision.h"
#include "Extension/PlayUI.h"
#include "Extension/MobSpawner.h"
#include "../Engine.h"
#include "../Manager/InputManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"
#include "../Entity/Object/AllObjects.h"
#include "../Entity/Component/AllComponents.h"

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
    mPlayer = InstantiatePlayer();
	BindEventListeners();

    // Camera //
    mCamera->SetTarget(mPlayer);

	// UI //
	mSceneUI->Init();
	SetSubState(EPlaySubState::PLAY);

	// Spawner //
	mMobSpawner->Init();
	mMobSpawner->SetPlayer(mPlayer);

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
		mTime += deltaTime;
		((CPlayUI*)mSceneUI)->SetGameTime(mTime);
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
	LoadTexture("Texture_OverlayBG", "OverlayBG.png");
	LoadTexture("Texture_GameOver", "GameOver.png");

    LoadTexture("Texture_MadForest", "MadForest.png");
    LoadTexture("Texture_MadForestTexturePack", "MadForestTexturePack.png");

    std::string charName = CGameDataManager::GetInst()->GetPlayerProfile()->GetName();
    LoadTexture("Texture_" + charName, (charName + ".png").c_str());

	LoadTexture("Texture_Boss", "BossAtlas.png");

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

    switch (CGameDataManager::GetInst()->GetPlayerProfile()->GetType())
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

void CPlayScene::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 경험치 관련
	EM->AddListener(EEventType::PLAYER_EXP_GAINED, [this](void* data)
	{
		float percent = *(float*)data;
		((CPlayUI*)mSceneUI)->SetExpPercent(percent);
	});

	// 레벨업 관련
	EM->AddListener(EEventType::PLAYER_LEVEL_UP, [this](void*)
	{
		((CPlayUI*)mSceneUI)->SetPlayerLevel(mPlayer->GetStatus()->GetLevel());
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_LevelUp")->Play();
		SetSubState(EPlaySubState::LVLUP);
	});

	// 체력 관련
	EM->AddListener(EEventType::PLAYER_HP_CHANGED, [this](void* data)
	{
		float percent = *(float*)data;
		((CPlayUI*)mSceneUI)->SetHealthPercent(percent);
	});

	// 죽음 관련
	EM->AddListener(EEventType::PLAYER_DIED, [this](void*)
	{
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CBGM>("BGM_MadForest")->Stop();
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_GameOver")->Play();
		SetSubState(EPlaySubState::GAMEOVER);
	});

	// 몬스터 스포너 관련
	EM->AddListener(EEventType::REGULAR_MOB_SPAWN, [this](void* data)
	{
		ERegularMobType type = (ERegularMobType)(*(int*)data);

		CEnemy* mob = nullptr;
		switch (type)
		{
		case ERegularMobType::SKELETON:
			break;
		}
		mob->GetTransform()->SetWorldPos(mMobSpawner->GetRandomSpawnPos());
		mob->GetChase()->SetTarget(mPlayer->GetTransform());
		mMobSpawner->RegisterMob(mob);
	});
	EM->AddListener(EEventType::SUBBOSS_MOB_SPAWN, [this](void* data)
	{
		ESubBossMobType type = (ESubBossMobType)(*(int*)data);

		CEnemy* mob = nullptr;
		switch (type)
		{
		case ESubBossMobType::REAPER:
			mob = InstantiateObject<CReaper, 1>("Enemy_Boss_Reaper");
			break;
		case ESubBossMobType::DROWNER:
			mob = InstantiateObject<CDrowner, 1>("Enemy_Boss_Drowner");
			break;
		}
		mob->GetTransform()->SetWorldPos(mMobSpawner->GetRandomSpawnPos());
		mob->GetChase()->SetTarget(mPlayer->GetTransform());
		mMobSpawner->RegisterMob(mob);
	});
}