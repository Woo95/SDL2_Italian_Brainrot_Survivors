#include "MoneyHUD.h"
#include "AllWidgets.h"

CMoneyHUD::CMoneyHUD()
{
	Construct();
}

CMoneyHUD::~CMoneyHUD()
{
}

void CMoneyHUD::Construct()
{
    CImage* panel = CWidgetUtils::AllocateWidget<CImage>("MoneyHUD_Image_Panel");
    panel->GetTransform()->SetRelativeScale(1.0f, 1.0f);
    panel->SetTexture("Texture_UIAtlas");
    panel->SetFrame("MoneyBGBox");
    panel->Set9SlicingCorner(FVector2D(7.f, 7.f));
    panel->SetCornerRatio(2.0f);
    AddChild(panel);

    CImage* moneyIcon = CWidgetUtils::AllocateWidget<CImage>("MoneyHUD_Image_MoneyIcon");
    moneyIcon->GetTransform()->SetRelativeScale(0.3f, 1.0f);
    moneyIcon->GetTransform()->SetRelativePos(0.05f, 0.0f);
    moneyIcon->SetTexture("Texture_UIAtlas");
    moneyIcon->SetFrame("MoneyIcon");
    AddChild(moneyIcon);

    mBalance = CWidgetUtils::AllocateWidget<CTextBlock>("MoneyHUD_Text_Balance");
    mBalance->GetTransform()->SetRelativeScale(0.6f, 0.55f);
    mBalance->GetTransform()->SetRelativePos(0.35f, 0.25f);
    mBalance->SetAlignment(ETextBlock::Alignment::RIGHT);
    mBalance->SetCharWidth(17);
    mBalance->SetFont("Font64_CourierPrime_Regular");
    mBalance->SetText("0");
    AddChild(mBalance);
}

void CMoneyHUD::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CMoneyHUD>(this);
}

void CMoneyHUD::SetBalance(int balance)
{
    mBalance->SetText(std::to_string(balance));
}