#include "MenuUI.h"
#include "../../Widget/AllWidgets.h"

CMenuUI::CMenuUI() :
    mCurrentState(EMenuUIState::PressToStart),
    mPressToStart(nullptr)
{
}

CMenuUI::~CMenuUI()
{
}

bool CMenuUI::Init()
{
    CImage* background = CWidgetUtils::AllocateWidget<CImage>("BGImage");
    background->GetTransform()->SetWorldScale(1280.f, 800.f);
    background->SetTexture("Texture_IntroBG");
    background->SetFrame("IntroBG");
    AddWidget(background);

    mPressToStart = CWidgetUtils::AllocateWidget<CPressToStartWidget, 1>("PressToStart");
    AddWidget(mPressToStart);

    mMainMenu = CWidgetUtils::AllocateWidget<CMainMenuWidget, 1>("MainMenu");
    AddWidget(mMainMenu);


    SetMenuState(EMenuUIState::PressToStart);

    return true;
}

void CMenuUI::SetMenuState(EMenuUIState newState)
{
    mCurrentState = newState;

    mPressToStart->Disable();
    mMainMenu->Disable();

    switch (newState)
    {
    case EMenuUIState::PressToStart:
        mPressToStart->Enable();
        break;
    case EMenuUIState::MainMenu:
        mMainMenu->Enable();
        break;
    case EMenuUIState::Options:
        break;
    case EMenuUIState::Start:
        break;
    case EMenuUIState::PowerUp:
        break;
    }
}