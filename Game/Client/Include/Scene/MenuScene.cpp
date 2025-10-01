#include "MenuScene.h"
#include "Extension/MenuUI.h"
#include "../Manager/SceneManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CMenuScene::CMenuScene()
{
    mSceneUI = new CMenuUI;
}

CMenuScene::~CMenuScene()
{
    SAFE_DELETE(mSceneUI);
}

bool CMenuScene::Enter(void* payload)
{
    BindEventListeners();

    CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_TitleIntro")->Play();
    
    mSceneUI->Init();
    SetSubState(EMenuSubState::START);
    
    return true;
}

bool CMenuScene::Exit()
{
	CEventManager::GetInst()->ClearListener();

    return true;
}

void CMenuScene::Update(float deltaTime)
{
    mSceneUI->Update(deltaTime);
}

void CMenuScene::LoadResources()
{
    LoadTexture("Texture_IntroBG", "IntroBG.png");
    LoadTexture("Texture_UIAtlas", "UIAtlas.png");
    LoadTexture("Texture_ItemAtlas", "ItemAtlas.png");

    LoadTexture("Texture_Tralala", "Tralala.png");
    LoadTexture("Texture_Sahur", "Sahur.png");
    LoadTexture("Texture_Bananini", "Bananini.png");

    LoadFont("Font32_CourierPrime_Regular", "CourierPrime_Regular.ttf", 32);
    LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

    LoadSFX("SFX_TitleIntro", "sfx_titleIntro.wav");
    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
    LoadSFX("SFX_PressOut", "sfx_pressOut.wav");

    LoadSFX("SFX_Character_Tralala", "sfx_character_tralalero_tralala.mp3");
    LoadSFX("SFX_Character_Sahur", "sfx_character_tung_tung_tung_sahur.mp3");
    LoadSFX("SFX_Character_Bananini", "sfx_character_chimpanzini_bananini.mp3");
}

void CMenuScene::SetSubState(EMenuSubState state)
{
    ((CMenuUI*)mSceneUI)->SetUIPanel(state);
}

void CMenuScene::BindEventListeners()
{
    CEventManager* EM = CEventManager::GetInst();

    // 씬 전환 관련
    EM->AddListener(EEventType::GOTO_PLAY_SCENE, [this](void*)
    {
        CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::PLAY);
    });
}