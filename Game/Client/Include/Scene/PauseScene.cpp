#include "PauseScene.h"
#include "../Manager/SceneManager.h"
#include "../Scene/UI/PauseUI.h"
#include "../Core/Input.h"

CPauseScene::CPauseScene()
{
	mSceneUI = new CPauseUI;
}

CPauseScene::~CPauseScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CPauseScene::Enter()
{
	mSceneUI->Init();

	return true;
}

bool CPauseScene::Exit()
{
	return true;
}

void CPauseScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	if (CInput::GetInst()->GetKeyState(SDL_SCANCODE_ESCAPE, EKey::State::PRESS))
		CSceneManager::GetInst()->ChangeRequest(ETransition::POP, ESceneState::PAUSE);
}

void CPauseScene::LoadResources()
{
	LoadFont("Font64_CourierPrime_Regular", "CourierPrime_Regular.ttf", 64);

	LoadSFX("SFX_PressIn", "sfx_pressIn.wav");
	LoadSFX("SFX_PressOut", "sfx_pressOut.wav");
}