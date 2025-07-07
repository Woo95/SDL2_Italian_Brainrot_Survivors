#include "PauseScene.h"
#include "../Manager/SceneManager.h"
#include "../Core/Input.h"

CPauseScene::CPauseScene()
{
}

CPauseScene::~CPauseScene()
{
}

bool CPauseScene::Enter()
{
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
}