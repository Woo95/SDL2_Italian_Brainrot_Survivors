#include "PlayUI.h"
#include "../../Manager/GameManager.h"
#include "../../Widget/AllWidgets.h"

CPlayUI::CPlayUI()
{
}

CPlayUI::~CPlayUI()
{
}

bool CPlayUI::Init()
{
    CPlayWidget* play = CWidgetUtils::AllocateWidget<CPlayWidget, 1>("UserWidget_Play");
    play->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    AddWidget(play);

    return true;
}
