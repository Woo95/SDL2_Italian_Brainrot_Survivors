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

    CExpBar* expBar = CWidgetUtils::AllocateWidget<CExpBar>("PlayUI_ExpBar");
    expBar->GetTransform()->SetWorldScale(resolution * FVector2D(0.85f, 0.05f));
    expBar->GetTransform()->SetWorldPos(resolution * (FVector2D(0.56f, 0.035f)));
    expBar->GetTransform()->SetPivot(0.5f, 0.5f);
    AddWidget(expBar);

    CPortrait* portrait = CWidgetUtils::AllocateWidget<CPortrait>("PlayUI_Portrait");
    portrait->GetTransform()->SetWorldScale(resolution * FVector2D(0.1f, 0.15f));
    portrait->GetTransform()->SetWorldPos(resolution * (FVector2D(0.07f, 0.086f)));
    portrait->GetTransform()->SetPivot(0.5f, 0.5f);
    portrait->SetPortrait(CGameDataManager::GetInst()->GetPlayerState()->GetSelectedCharacterName() + "Portrait");
    AddWidget(portrait);

    return true;
}