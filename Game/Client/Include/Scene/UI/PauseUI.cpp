#include "PauseUI.h"
#include "../../Manager/GameManager.h"
#include "../../Widget/AllWidgets.h"

CPauseUI::CPauseUI()
{
}

CPauseUI::~CPauseUI()
{
}

bool CPauseUI::Init()
{
    CPauseWidget* pause = CWidgetUtils::AllocateWidget<CPauseWidget, 1>("UserWidget_Pause");
    pause->GetTransform()->SetWorldScale(CGameManager::GetInst()->GetResolution());
    AddWidget(pause);

    return true;
}
