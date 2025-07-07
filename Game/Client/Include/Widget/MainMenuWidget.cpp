#include "MainMenuWidget.h"
#include "AllWidgets.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"

CMainMenuWidget::CMainMenuWidget()
{
	Construct();
}

CMainMenuWidget::~CMainMenuWidget()
{
}

void CMainMenuWidget::Construct()
{
    CImage* menuTopBar = CWidgetUtils::AllocateWidget<CImage>("Image_MenuTopBar");
    menuTopBar->GetTransform()->SetRelativeScale(FVector2D(1.0f, 0.09625f));
    menuTopBar->SetTexture("Texture_UIAtlas");
    menuTopBar->SetFrame("MenuTopBar");
    menuTopBar->SetAlpha(180);
    AddChild(menuTopBar);

    CTextBlock* name = CWidgetUtils::AllocateWidget<CTextBlock>("Text_Name");
    name->GetTransform()->SetRelativeScale(FVector2D(0.15625f, 0.05f));
    name->GetTransform()->SetRelativePos(FVector2D(0.03f, 0.024f));
    name->SetAlignment(ETextBlock::Alignment::CENTER);
    name->SetCharWidth(50.f);
    name->SetFont("Font64_CourierPrime_Regular");
    name->SetText("Chaewan Woo");
    AddChild(name);

    CMoneyHUDWidget* moneyHUD = CWidgetUtils::AllocateWidget<CMoneyHUDWidget, 1>("UserWidget_MoneyHUD");
    moneyHUD->GetTransform()->SetRelativeScale(FVector2D(0.1758f, 0.08f));
    moneyHUD->GetTransform()->SetRelativePos(FVector2D(0.4121f, 0.009625f));
    AddChild(moneyHUD);

    mBtnQuit = CreateButton("Quit", "RedButton", FVector2D(0.08515f, 0.075f), "QUIT", FVector2D(0.5f, 0.4f));
    mBtnQuit->GetTransform()->SetRelativePos(FVector2D(0.34375f, 0.048f));
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnQuit->AddCallback(EButton::InputEvent::RELEASE, []() {SDL_Event quitEvent; quitEvent.type = SDL_QUIT; SDL_PushEvent(&quitEvent);});

    mBtnOption = CreateButton("Option", "BlueButton", FVector2D(0.08515f, 0.075f), "OPTIONS", FVector2D(0.733f, 0.4f));
    mBtnOption->GetTransform()->SetRelativePos(FVector2D(0.65625f, 0.048f));
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnOption->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mOptionPanel);});

    mBtnBack = CreateButton("Back", "RedButton", FVector2D(0.08515f, 0.075f), "BACK", FVector2D(0.45f, 0.4f));
    mBtnBack->GetTransform()->SetRelativePos(FVector2D(0.65625f, 0.048f));
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressOut")->Play();});
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->HidePanel();});
    mBtnBack->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->mCharSelectPanel->OnBackButton();});

    CButton* btnStart = CreateButton("Start", "BlueButton", FVector2D(0.1758f, 0.08125f), "START", FVector2D(0.533f, 0.625f));
    btnStart->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.653125f));
    btnStart->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnStart->SetCornerRatio(2.0f);
    btnStart->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    btnStart->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mCharSelectPanel);});

    CButton* btnPowerUp = CreateButton("PowerUp", "GreenButton", FVector2D(0.1422f, 0.08f), "POWER UP", FVector2D(0.823f, 0.575f));
    btnPowerUp->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.8275f));
    btnPowerUp->Set9SlicingCorner(FVector2D(10.f, 7.f));
    btnPowerUp->SetCornerRatio(2.0f);
    btnPowerUp->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});

    CButton* btnCredits = CreateButton("Credits", "BlueCircularButton", FVector2D(0.12f, 0.035f), "credits", FVector2D(0.6f, 0.8f));
    btnCredits->GetTransform()->SetRelativePos(FVector2D(0.5f, 0.945f));
    btnCredits->Set9SlicingCorner(FVector2D(7.f, 7.f));
    btnCredits->SetCornerRatio(2.0f);
    btnCredits->AddCallback(EButton::InputEvent::RELEASE, []() {CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("SFX_PressIn")->Play();});
    btnCredits->AddCallback(EButton::InputEvent::RELEASE, [this]() {this->ShowPanel(mCreditsPanel);});

    mOptionPanel = CWidgetUtils::AllocateWidget<COptionPanelWidget, 1>("UserWidget_OptionPanel");
    mOptionPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.85f));
    mOptionPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.119f));
    AddChild(mOptionPanel);

    mCharSelectPanel = CWidgetUtils::AllocateWidget<CCharSelectPanelWidget, 1>("UserWidget_CharSelectPanel");
    mCharSelectPanel->GetTransform()->SetRelativeScale(FVector2D(1.0f, 0.85f));
    mCharSelectPanel->GetTransform()->SetRelativePos(FVector2D(0.0f, 0.119f));
    AddChild(mCharSelectPanel);

    mCreditsPanel = CWidgetUtils::AllocateWidget<CCreditsPanelWidget, 1>("UserWidget_CreditsPanel");
    mCreditsPanel->GetTransform()->SetRelativeScale(FVector2D(0.46f, 0.85f));
    mCreditsPanel->GetTransform()->SetRelativePos(FVector2D(0.27f, 0.119f));
    AddChild(mCreditsPanel);

    HidePanel();
}

void CMainMenuWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMainMenuWidget>(this);
}

void CMainMenuWidget::ShowPanel(CWidget* panel)
{
    mBtnQuit->Disable();
    mBtnOption->Disable();
    mBtnBack->Enable();
    panel->Enable();
}

void CMainMenuWidget::HidePanel()
{
    mBtnQuit->Enable();
    mBtnOption->Enable();
    mBtnBack->Disable();
    mOptionPanel->Disable();
    mCharSelectPanel->Disable();
    mCreditsPanel->Disable();
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
    text->GetTransform()->SetRelativeScale(textSize);
    text->GetTransform()->SetPivot(0.5f, 0.5f);
    text->GetTransform()->SetRelativePos(0.0f, 0.0f);
    text->SetFont("Font64_CourierPrime_Regular");
    text->SetText(textLabel);

    return button;
}