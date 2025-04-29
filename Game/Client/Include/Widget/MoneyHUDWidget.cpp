#include "MoneyHUDWidget.h"
#include "AllWidgets.h"

CMoneyHUDWidget::CMoneyHUDWidget()
{
	Construct();
}

CMoneyHUDWidget::~CMoneyHUDWidget()
{
}

void CMoneyHUDWidget::Construct()
{
    CImage* backgroundBox = CWidgetUtils::AllocateWidget<CImage>("Image_MoneyBGBox");
    backgroundBox->GetTransform()->SetRelativeScale(1.0f, 1.0f);
    backgroundBox->SetTexture("Texture_UIAtlas");
    backgroundBox->SetFrame("MoneyBGBox");
    backgroundBox->Set9SlicingCorner(FVector2D(7.f, 7.f));
    backgroundBox->SetCornerRatio(2.0f);
    AddChild(backgroundBox);

    CImage* moneyIcon = CWidgetUtils::AllocateWidget<CImage>("Image_MoneyIcon");
    moneyIcon->GetTransform()->SetRelativeScale(0.3f, 1.0f);
    moneyIcon->GetTransform()->SetRelativePos(0.05f, 0.0f);
    moneyIcon->SetTexture("Texture_UIAtlas");
    moneyIcon->SetFrame("MoneyIcon");
    AddChild(moneyIcon);

    mBalanceText = CWidgetUtils::AllocateWidget<CTextBlock>("Text_mMoneyAmount");
    mBalanceText->GetTransform()->SetRelativeScale(0.6f, 0.55f);
    mBalanceText->GetTransform()->SetRelativePos(0.35f, 0.25f);
    mBalanceText->SetAlignment(ETextBlock::Alignment::RIGHT);
    mBalanceText->SetCharWidth(17);
    mBalanceText->SetFont("Font64_CourierPrime_Regular");
    mBalanceText->SetText("0");
    AddChild(mBalanceText);
}

void CMoneyHUDWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CMoneyHUDWidget>(this);
}

void CMoneyHUDWidget::SetBalance(int balance)
{
    mBalanceText->SetText(std::to_string(balance));
}