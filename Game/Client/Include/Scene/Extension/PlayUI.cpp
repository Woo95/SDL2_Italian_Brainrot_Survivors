#include "PlayUI.h"
#include "../../Engine.h"
#include "../../Widget/AllWidgets.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
    const FVector2D& resolution = CEngine::GetInst()->GetResolution();

	mPlay = CWidgetUtils::AllocateWidget<CPlayPanel, 1>("PlayUI_PlayPanel");
    mPlay->GetTransform()->SetWorldScale(resolution);
	mPlay->Disable();
	AddWidget(mPlay);

	mPause = CWidgetUtils::AllocateWidget<CPausePanel, 1>("PlayUI_PausePanel");
    mPause->GetTransform()->SetWorldScale(resolution);
	mPause->Disable();
	AddWidget(mPause);

	mLevelUp = CWidgetUtils::AllocateWidget<CLevelUpPanel, 1>("PlayUI_LevelUpPanel");
	mLevelUp->GetTransform()->SetWorldScale(resolution);
	mLevelUp->Disable();
	AddWidget(mLevelUp);

	mGameOver = CWidgetUtils::AllocateWidget<CGameOverPanel, 1>("PlayUI_GameOverPanel");
	mGameOver->GetTransform()->SetWorldScale(resolution);
	mGameOver->Disable();
	AddWidget(mGameOver);

    return true;
}

void CPlayUI::SetUIPanel(EPlaySubState state)
{
	switch (state)
	{
	case EPlaySubState::PLAY:
		mPlay->Enable();
		mPause->Disable();
		mLevelUp->Disable();
		mGameOver->Disable();

		mPause->HideOptionPanel();
		break;
	case EPlaySubState::PAUSE:
		mPause->Enable();
		break;
	case EPlaySubState::LVLUP:
		mLevelUp->Enable();
		break;
	case EPlaySubState::GAMEOVER:
		mGameOver->Enable();
		break;
	}
}

void CPlayUI::SetHealthPercent(float percent)
{
    mPlay->SetHealthPercent(percent);
}

void CPlayUI::SetExpPercent(float percent)
{
    mPlay->SetExpPercent(percent);
}

void CPlayUI::SetPlayerLevel(int level)
{
    mPlay->SetPlayerLevel(level);
}

void CPlayUI::SetKillCounter(int count)
{
    mPlay->SetKillCounter(count);
}

void CPlayUI::SetGameTime(float seconds)
{
    mPlay->SetGameTime(seconds);
}