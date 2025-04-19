#include "MenuScene.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"

CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
}

bool CMenuScene::Enter()
{
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
    LoadSFX("SFX_TitleIntro", "sfx_titleIntro.wav");
}