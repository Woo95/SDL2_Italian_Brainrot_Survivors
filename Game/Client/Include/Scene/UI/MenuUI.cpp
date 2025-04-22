#include "MenuUI.h"
#include "../../Widget/AllWidgets.h"

CMenuUI::CMenuUI()
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

    return true;
}