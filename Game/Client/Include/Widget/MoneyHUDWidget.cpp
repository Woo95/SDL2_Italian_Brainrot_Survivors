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
    mBackgroundBox = CWidgetUtils::AllocateWidget<CImage>("Image_MoneyBGBox");
    mBackgroundBox->GetTransform()->SetRelativeScale(1.0f, 1.0f);
    mBackgroundBox->SetTexture("Texture_UIAtlas");
    mBackgroundBox->SetFrame("MoneyBGBox");
    mBackgroundBox->Set9SlicingCorner(FVector2D(7.f, 7.f));
    mBackgroundBox->SetCornerRatio(2.0f);
    AddChild(mBackgroundBox);

    mMoneyIcon = CWidgetUtils::AllocateWidget<CImage>("Image_MoneyIcon");
    mMoneyIcon->GetTransform()->SetRelativeScale(0.3f, 1.f);
    mMoneyIcon->GetTransform()->SetRelativePos(0.05f, 0.0f);
    mMoneyIcon->SetTexture("Texture_UIAtlas");
    mMoneyIcon->SetFrame("MoneyIcon");
    AddChild(mMoneyIcon);

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