#include "MenuUI.h"
#include "../../Manager/GameManager.h"
#include "../../Widget/AllWidgets.h"

CMenuUI::CMenuUI()
{
}

CMenuUI::~CMenuUI()
{
}

bool CMenuUI::Init()
{
    CImage* background = CWidgetUtils::AllocateWidget<CImage>("Image_BGImage");
    background->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    background->SetTexture("Texture_IntroBG");
    background->SetFrame("IntroBG");
    AddWidget(background);

    mPressToStart = CWidgetUtils::AllocateWidget<CPressToStartWidget, 1>("UserWidget_PressToStart");
    mPressToStart->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    AddWidget(mPressToStart);

    mMainMenu = CWidgetUtils::AllocateWidget<CMainMenuWidget, 1>("UserWidget_MainMenu");
    mMainMenu->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    AddWidget(mMainMenu);

    SetMenuState(EMenuUIState::PressToStart);

    return true;
}

void CMenuUI::SetMenuState(EMenuUIState state)
{
    switch (state)
    {
    case EMenuUIState::PressToStart:
        mPressToStart->Enable();
        mMainMenu->Disable();
        break;
    case EMenuUIState::MainMenu:
        mMainMenu->Enable();
        mPressToStart->Disable();
        break;
    }
}