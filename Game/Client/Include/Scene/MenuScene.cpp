#include "MenuScene.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"
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

    CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(0.1f);
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

    LoadFont("Font32_CourierPrime_Regular", "CourierPrime_Regular.ttf", 32);
    LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

    LoadSFX("SFX_TitleIntro", "sfx_titleIntro.wav");
    LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
}