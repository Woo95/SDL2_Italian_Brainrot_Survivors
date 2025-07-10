#include "GameOverScene.h"
#include "../Scene/UI/GameOverUI.h"

CGameOverScene::CGameOverScene()
{
	mSceneUI = new CGameOverUI;
}

CGameOverScene::~CGameOverScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CGameOverScene::Enter()
{
	mSceneUI->Init();

	return true;
}

bool CGameOverScene::Exit()
{
	return true;
}

void CGameOverScene::LoadResources()
{
	LoadTexture("Texture_IntroBG", "IntroBG.png");
	LoadTexture("Texture_UIAtlas", "UIAtlas.png");

	LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

	LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}