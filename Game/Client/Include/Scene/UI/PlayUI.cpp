#include "PlayUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"
#include "../../Manager/SceneManager.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

    CButton* btnPause = CWidgetUtils::AllocateWidget<CButton>("Button_PAUSE");
    btnPause->GetTransform()->SetWorldScale(resolution * FVector2D(0.03f, 0.08f));
    btnPause->GetTransform()->SetWorldPos(resolution * (FVector2D(0.955f, 0.075f)));
    btnPause->SetTexture("Texture_UIAtlas");
    btnPause->SetFrame("PauseButton");
    btnPause->SetAlpha(120);
    btnPause->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::PUSH, ESceneState::PAUSE);});
    AddWidget(btnPause);

    return true;
}