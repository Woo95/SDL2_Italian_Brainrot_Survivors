#include "PlayUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/SoundManager.h"

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
		break;
	case EPlaySubState::PAUSE:
		mPause->Enable();
		break;
	case EPlaySubState::LVLUP:
		CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_LevelUp")->Play();
		mLevelUp->Enable();
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