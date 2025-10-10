#include "PlayPanel.h"
#include "AllWidgets.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/GameData/GameDataManager.h"
#include "../Manager/Data/GameData/PlayerProfile.h"

CPlayPanel::CPlayPanel()
{
	Construct();
}

CPlayPanel::~CPlayPanel()
{
}

void CPlayPanel::Construct()
{
	CButton* btnPause = CWidgetUtils::AllocateWidget<CButton>("PlayUI_Button_Pause");
	btnPause->GetTransform()->SetRelativeScale(FVector2D(0.03f, 0.08f));
	btnPause->GetTransform()->SetRelativePos(FVector2D(0.955f, 0.075f));
	btnPause->SetTexture("Texture_UIAtlas");
	btnPause->SetFrame("PauseButton");
	btnPause->SetAlpha(120);
	btnPause->AddCallback(EButton::InputEvent::RELEASE, []() {CEventManager::GetInst()->Broadcast(EEventType::GOTO_PLAY_SUB_STATE_PAUSE);});
	AddChild(btnPause);

	CPortrait* portrait = CWidgetUtils::AllocateWidget<CPortrait>("PlayUI_Portrait");
	portrait->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.15f));
	portrait->GetTransform()->SetRelativePos(FVector2D(0.07f, 0.086f));
	portrait->GetTransform()->SetPivot(0.5f, 0.5f);
	portrait->SetPortrait(CGameDataManager::GetInst()->GetPlayerProfile()->GetName() + "Portrait");
	AddChild(portrait);

	mHealthBar = CWidgetUtils::AllocateWidget<CProgressBar, 2>("PlayUI_ProgressBar_Hp");
	mHealthBar->GetTransform()->SetRelativeScale(FVector2D(0.1f, 0.022f));
	mHealthBar->GetTransform()->SetRelativePos(FVector2D(0.07f, 0.18f));
	mHealthBar->GetTransform()->SetPivot(0.5f, 0.5f);
	mHealthBar->SetTexture("Texture_UIAtlas");
	mHealthBar->SetFrame("StatusBar");
	mHealthBar->SetColor(EProgBar::State::BACK, 25, 0, 25);
	mHealthBar->SetColor(EProgBar::State::FILL, 255, 0, 0);
	mHealthBar->SetPercent(1.0f);
	AddChild(mHealthBar);

	mExpBar = CWidgetUtils::AllocateWidget<CExpBar, 1>("PlayUI_ExpBar");
	mExpBar->GetTransform()->SetRelativeScale(FVector2D(0.85f, 0.05f));
	mExpBar->GetTransform()->SetRelativePos(FVector2D(0.56f, 0.035f));
	mExpBar->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(mExpBar);

	mKillCounter = CWidgetUtils::AllocateWidget<CKillCounter, 1>("PlayUI_KillCounter");
	mKillCounter->GetTransform()->SetRelativeScale(FVector2D(0.08f, 0.035f));
	mKillCounter->GetTransform()->SetRelativePos(FVector2D(0.9f, 0.093f));
	mKillCounter->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(mKillCounter);

	mCoinCounter = CWidgetUtils::AllocateWidget<CCoinCounter, 1>("PlayUI_CoinCounter");
	mCoinCounter->GetTransform()->SetRelativeScale(FVector2D(0.08f, 0.035f));
	mCoinCounter->GetTransform()->SetRelativePos(FVector2D(0.9f, 0.138f));
	mCoinCounter->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(mCoinCounter);

	mTimeHUD = CWidgetUtils::AllocateWidget<CTimeHUD, 1>("PlayUI_TimeHUD");
	mTimeHUD->GetTransform()->SetRelativeScale(FVector2D(0.09f, 0.05f));
	mTimeHUD->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.1f));
	mTimeHUD->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(mTimeHUD);

	mInventory = CWidgetUtils::AllocateWidget<CInventoryPanel, 1>("PlayUI_InventoryPanel");
	mInventory->GetTransform()->SetRelativeScale(FVector2D(0.2109f, 0.115f));
	mInventory->GetTransform()->SetRelativePos(FVector2D(0.24f, 0.133f));
	mInventory->GetTransform()->SetPivot(0.5f, 0.5f);
	AddChild(mInventory);
}

void CPlayPanel::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CPlayPanel>(this);
}

void CPlayPanel::SetHealthPercent(float percent)
{
	mHealthBar->SetPercent(percent);
}

void CPlayPanel::SetExpPercent(float percent)
{
	mExpBar->SetPercent(percent);
}

void CPlayPanel::SetPlayerLevel(int level)
{
	mExpBar->SetLevelText(level);
}

void CPlayPanel::SetKillCounter(int count)
{
	mKillCounter->SetCountText(count);
}

void CPlayPanel::SetCoinCounter(int count)
{
	mCoinCounter->SetCountText(count);
}

void CPlayPanel::SetGameTime(float seconds)
{
	mTimeHUD->SetTimeText(seconds);
}

void CPlayPanel::SetInventorySlot(EWeaponType type)
{
	mInventory->AddWeapon(type);
}

void CPlayPanel::SetInventorySlot(EPowerUpType type)
{
	mInventory->AddPowerUp(type);
}