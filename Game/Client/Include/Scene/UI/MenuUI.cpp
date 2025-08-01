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

    CImage* background = CWidgetUtils::AllocateWidget<CImage>("MenuUI_Image_MenuBG");
    background->GetTransform()->SetWorldScale(resolution);
    background->SetTexture("Texture_IntroBG");
    background->SetFrame("IntroBG");
    AddWidget(background);

    mPressToStart = CWidgetUtils::AllocateWidget<CPressToStartPanel, 1>("MenuUI_PressToStart");
    mPressToStart->GetTransform()->SetWorldScale(resolution);
    AddWidget(mPressToStart);

    mMainMenu = CWidgetUtils::AllocateWidget<CMainMenuPanel, 1>("MenuUI_MainMenuPanel");
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