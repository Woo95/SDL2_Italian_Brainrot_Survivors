#include "ResultScene.h"
#include "../Scene/Extension/ResultUI.h"

CResultScene::CResultScene()
{
	mSceneUI = new CResultUI;
}

CResultScene::~CResultScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CResultScene::Enter()
{
	mSceneUI->Init();

	return true;
}

bool CResultScene::Exit()
{
	return true;
}

void CResultScene::LoadResources()
{
	LoadTexture("Texture_OverlayBG", "OverlayBG.png");
	LoadTexture("Texture_UIAtlas", "UIAtlas.png");

	LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

	LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}