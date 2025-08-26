#include "PlayUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/Data/GameData/GameDataManager.h"
#include "../../Manager/Data/GameData/PlayerState.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

    CButton* btnPause = CWidgetUtils::AllocateWidget<CButton>("PlayUI_Button_Pause");
    btnPause->GetTransform()->SetWorldScale(resolution * FVector2D(0.03f, 0.08f));
    btnPause->GetTransform()->SetWorldPos(resolution * (FVector2D(0.955f, 0.075f)));
    btnPause->SetTexture("Texture_UIAtlas");
    btnPause->SetFrame("PauseButton");
    btnPause->SetAlpha(120);
    btnPause->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::PUSH, ESceneState::PAUSE);});
    AddWidget(btnPause);

    CPortrait* portrait = CWidgetUtils::AllocateWidget<CPortrait>("PlayUI_Portrait");
    portrait->GetTransform()->SetWorldScale(resolution * FVector2D(0.1f, 0.15f));
    portrait->GetTransform()->SetWorldPos(resolution * (FVector2D(0.07f, 0.086f)));
    portrait->GetTransform()->SetPivot(0.5f, 0.5f);
    portrait->SetPortrait(CGameDataManager::GetInst()->GetPlayerState()->GetName() + "Portrait");
    AddWidget(portrait);

    mHealthBar = CWidgetUtils::AllocateWidget<CProgressBar, 2>("PlayUI_ProgressBar_Hp");
    mHealthBar->GetTransform()->SetWorldScale(resolution * FVector2D(0.1f, 0.022f));
    mHealthBar->GetTransform()->SetWorldPos(resolution * (FVector2D(0.07f, 0.18f)));
    mHealthBar->GetTransform()->SetPivot(0.5f, 0.5f);
    mHealthBar->SetTexture("Texture_UIAtlas");
    mHealthBar->SetFrame("StatusBar");
    mHealthBar->SetColor(EProgBar::State::BACK, 25, 0, 25);
    mHealthBar->SetColor(EProgBar::State::FILL, 255, 0, 0);
    mHealthBar->SetPercent(1.0f);
    AddWidget(mHealthBar);

    mExpBar = CWidgetUtils::AllocateWidget<CExpBar, 1>("PlayUI_ExpBar");
    mExpBar->GetTransform()->SetWorldScale(resolution * FVector2D(0.85f, 0.05f));
    mExpBar->GetTransform()->SetWorldPos(resolution * (FVector2D(0.56f, 0.035f)));
    mExpBar->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(mExpBar);

    mKillCounter = CWidgetUtils::AllocateWidget<CKillCounter, 1>("PlayUI_KillCounter");
    mKillCounter->GetTransform()->SetWorldScale(resolution * FVector2D(0.08f, 0.035f));
    mKillCounter->GetTransform()->SetWorldPos(resolution * (FVector2D(0.9f, 0.093f)));
    mKillCounter->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(mKillCounter);

    mTimeHUD = CWidgetUtils::AllocateWidget<CTimeHUD, 1>("PlayUI_TimeHUD");
    mTimeHUD->GetTransform()->SetWorldScale(resolution * FVector2D(0.09f, 0.05f));
    mTimeHUD->GetTransform()->SetWorldPos(resolution * (FVector2D(0.5f, 0.1f)));
    mTimeHUD->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(mTimeHUD);

    return true;
}

void CPlayUI::SetHealthPercent(float percent)
{
    mHealthBar->SetPercent(percent);
}

void CPlayUI::SetExpPercent(float percent)
{
    mExpBar->SetPercent(percent);
}

void CPlayUI::SetPlayerLevel(int level)
{
    mExpBar->SetLevelText(level);
}

void CPlayUI::SetKillCounter(int count)
{
    mKillCounter->SetCountText(count);
}

void CPlayUI::SetGameTime(float seconds)
{
    mTimeHUD->SetTimeText(seconds);
}