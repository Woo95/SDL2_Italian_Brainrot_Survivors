#include "MenuScene.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Scene/UI/MenuUI.h"

CMenuScene::CMenuScene()
{
    mSceneUI = new CMenuUI;
}

CMenuScene::~CMenuScene()
{
    SAFE_DELETE(mSceneUI);
}

bool CMenuScene::Enter()
{
    mSceneUI->Init();

    CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_TitleIntro")->Play();

    return true;
}

bool CMenuScene::Exit()
{
    return true;
}

void CMenuScene::LoadResources()
{
    LoadTexture("Texture_IntroBG", "IntroBG.png");
    LoadTexture("Texture_UIAtlas", "UIAtlas.png");

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