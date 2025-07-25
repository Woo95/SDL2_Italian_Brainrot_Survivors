#include "MenuUI.h"
#include "../../Widget/AllWidgets.h"
#include "../../Manager/GameManager.h"

CMenuUI::CMenuUI()
{
}

CMenuUI::~CMenuUI()
{
}

bool CMenuUI::Init()
{
    const FVector2D& resolution = CGameManager::GetInst()->GetResolution();

    CImage* background = CWidgetUtils::AllocateWidget<CImage>("Image_IntroBG");
    background->GetTransform()->SetWorldScale(resolution);
    background->SetTexture("Texture_IntroBG");
    background->SetFrame("IntroBG");
    AddWidget(background);

    mPressToStart = CWidgetUtils::AllocateWidget<CPressToStartWidget, 1>("UserWidget_PressToStart");
    mPressToStart->GetTransform()->SetWorldScale(resolution);
    AddWidget(mPressToStart);

    mMainMenu = CWidgetUtils::AllocateWidget<CMainMenuWidget, 1>("UserWidget_MainMenu");
    mMainMenu->GetTransform()->SetWorldScale(resolution);
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