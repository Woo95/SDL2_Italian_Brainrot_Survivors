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
    mPlay = CWidgetUtils::AllocateWidget<CPlayWidget, 1>("UserWidget_Play");
    mPlay->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    AddWidget(mPlay);

    return true;
}