#include "PlayUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

	mPlay = CWidgetUtils::AllocateWidget<CPlayPanel, 1>("PlayUI_PlayPanel");
    mPlay->GetTransform()->SetWorldScale(resolution);
	AddWidget(mPlay);

	mPause = CWidgetUtils::AllocateWidget<CPausePanel, 1>("PlayUI_PausePanel");
    mPause->GetTransform()->SetWorldScale(resolution);
	mPause->Disable();
	AddWidget(mPause);

    return true;
}

void CPlayUI::SetUIPanel(EPlaySubState state)
{
	switch (state)
	{
	case EPlaySubState::PLAY:
		mPause->Disable();
		break;
	case EPlaySubState::PAUSE:
		mPause->Enable();
		break;
	case EPlaySubState::LVLUP:
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