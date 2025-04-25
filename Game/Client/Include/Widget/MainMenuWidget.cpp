#include "MainMenuWidget.h"
#include "AllWidgets.h"

CMainMenuWidget::CMainMenuWidget()
{
	Construct();
}

CMainMenuWidget::~CMainMenuWidget()
{
}

void CMainMenuWidget::Construct()
{
    SetInteractable(true);
    GetTransform()->SetWorldScale(1280.f, 800.f);

    const FVector2D& parentScale = GetTransform()->GetWorldScale();

    mMenuTopBar = CWidgetUtils::AllocateWidget<CImage>("Image_MenuTopBar");
    mMenuTopBar->GetTransform()->SetWorldScale(parentScale.x, 77.f);
    mMenuTopBar->SetTexture("Texture_UIAtlas");
    mMenuTopBar->SetFrame("MenuTopBar");
    mMenuTopBar->SetAlpha(180);
    AddChild(mMenuTopBar);

    mName = CWidgetUtils::AllocateWidget<CTextBlock>("Text_name");
    mName->GetTransform()->SetWorldScale(200.f, 40.f);
    mName->GetTransform()->SetWorldPos(parentScale.x * 0.03f, mMenuTopBar->GetTransform()->GetWorldScale().y * 0.25f);
    mName->SetFont("Font64_CourierPrime_Regular");
    mName->SetText("Chaewan Woo");
    AddChild(mName);

    mMoneyHUD = CWidgetUtils::AllocateWidget<CMoneyHUDWidget, 1>("UserWidget_MoneyHUD");
    mMoneyHUD->GetTransform()->SetWorldScale(225.f, 64.f);
    mMoneyHUD->GetTransform()->SetWorldPos((parentScale.x - mMoneyHUD->GetTransform()->GetWorldScale().x) * 0.5f, mMenuTopBar->GetTransform()->GetWorldScale().y * 0.1f);
    AddChild(mMoneyHUD);

    mBtnQuit = CreateButton("Quit", "RedButton", FVector2D(109.f, 60.f), "QUIT", FVector2D(55.f, 25.f));
    mBtnQuit->GetTransform()->SetWorldPos(parentScale.x * 0.5f - 200.f, mMenuTopBar->GetTransform()->GetWorldScale().y * 0.5f);

    mBtnOption = CreateButton("Option", "BlueButton", FVector2D(109.f, 60.f), "OPTIONS", FVector2D(80.f, 25.f));
    mBtnOption->GetTransform()->SetWorldPos(parentScale.x * 0.5f + 200.f, mMenuTopBar->GetTransform()->GetWorldScale().y * 0.5f );

    mStart = CreateButton("Start", "BlueButton", FVector2D(225.f, 65.f), "START", FVector2D(120.f, 40.f));
    mStart->GetTransform()->SetWorldPos(parentScale.x * 0.5f, parentScale.y - 277.f);
    mStart->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mStart->SetCornerRatio(2.0f);

    mPowerUp = CreateButton("PowerUp", "GreenButton", FVector2D(182.f, 64.f), "POWER UP", FVector2D(150.f, 35.f));
    mPowerUp->GetTransform()->SetWorldPos(parentScale.x * 0.5f, parentScale.y - 138.f);
    mPowerUp->Set9SlicingCorner(FVector2D(10.f, 7.f));
    mPowerUp->SetCornerRatio(2.0f);
}

void CMainMenuWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMainMenuWidget>(this);
}

CButton* CMainMenuWidget::CreateButton(const std::string& widgetName, const std::string& buttonFrame, const FVector2D& buttonSize, const std::string& textLabel, const FVector2D& textSize)
{
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button_" + widgetName);
    button->GetTransform()->SetWorldScale(buttonSize);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("Texture_UIAtlas");
    button->SetFrame(buttonFrame);
    AddChild(button);

    CTextBlock* text = CWidgetUtils::AllocateWidget<CTextBlock>("Text_" + widgetName);
    button->AddChild(text);
    text->GetTransform()->SetWorldScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.f, 0.f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}