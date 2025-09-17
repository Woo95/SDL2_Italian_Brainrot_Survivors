#include "PlayUI.h"
#include "../../Engine.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/EventManager.h"
#include "../../Entity/Object/Player.h"
#include "../../Entity/Component/AllComponents.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
	BindEventListeners();

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

void CPlayUI::SetLevelUpChoice(std::vector<FItem> pool)
{
	const std::vector<CLevelUpSlot*>& slots = mLevelUp->GetSlots();
	for (size_t i = 0; i < slots.size(); i++)
	{
		if (i < pool.size())
		{
			slots[i]->UpdateSlot(pool[i]);
			slots[i]->Enable();
		}
		else
		{
			slots[i]->Disable();
		}
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

void CPlayUI::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 경험치 관련
	EM->AddListener(EEventType::PLAYER_EXP_GAINED, [this](void* data)
	{
		float percent = *(float*)data;
		SetExpPercent(percent);
	});

	// 체력 관련
	EM->AddListener(EEventType::PLAYER_HP_CHANGED, [this](void* data)
	{
		float percent = *(float*)data;
		SetHealthPercent(percent);
	});

	// 레벨업 관련
	EM->AddListener(EEventType::PLAYER_LEVEL_UP, [this](void* data)
	{
		CPlayer* player = (CPlayer*)data;
		SetLevelUpChoice(player->GetLevelUpPool());
		SetPlayerLevel(player->GetStatus()->GetLevel() - player->GetStatus()->GetPendingLevelUps());
	});
}