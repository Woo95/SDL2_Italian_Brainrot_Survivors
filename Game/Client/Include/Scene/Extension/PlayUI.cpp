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

void CPlayUI::BindEventListeners()
{
	CEventManager* EM = CEventManager::GetInst();

	// 체력 관련
	EM->AddListener(EEventType::PLAYER_HP_CHANGED, [this](void* data)
	{
		float percent = *(float*)data;
		mPlay->SetHealthPercent(percent);
	});

	// 경험치 관련
	EM->AddListener(EEventType::PLAYER_EXP_GAINED, [this](void* data)
	{
		float percent = *(float*)data;
		mPlay->SetExpPercent(percent);
	});

	// 레벨업 관련
	EM->AddListener(EEventType::PLAYER_LEVEL_UP_BEGIN, [this](void* data)
	{
		int level = *(int*)data;
		mPlay->SetPlayerLevel(level);
	});
	EM->AddListener(EEventType::PLAYER_LEVEL_UP_CHOICE, [this](void* data)
	{
		std::vector<FItem>& pool = *(std::vector<FItem>*)data;
		mLevelUp->SetLevelUpChoicePool(pool);
	});
	EM->AddListener(EEventType::PLAYER_LEVEL_UP_SELECT, [this](void* item)
	{
		FItem selectedItem = *(FItem*)item;
		if (selectedItem.level > 0)
			return;

		switch (selectedItem.category)
		{
		case EItemCategory::POWERUP:
			mPlay->SetInventorySlot((EPowerUpType)selectedItem.type);
			break;
		case EItemCategory::WEAPON:
			mPlay->SetInventorySlot((EWeaponType)selectedItem.type);
			break;
		}
	});
}